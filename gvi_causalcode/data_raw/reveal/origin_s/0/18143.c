bool mysql_show_grants ( THD * thd , LEX_USER * lex_user ) {
 ulong want_access ;
 uint counter , index ;
 int error = 0 ;
 ACL_USER * acl_user ;
 ACL_DB * acl_db ;
 char buff [ 1024 ] ;
 Protocol * protocol = thd -> protocol ;
 DBUG_ENTER ( "mysql_show_grants" ) ;
 LINT_INIT ( acl_user ) ;
 if ( ! initialized ) {
 my_error ( ER_OPTION_PREVENTS_STATEMENT , MYF ( 0 ) , "--skip-grant-tables" ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 rw_rdlock ( & LOCK_grant ) ;
 VOID ( pthread_mutex_lock ( & acl_cache -> lock ) ) ;
 acl_user = find_acl_user ( lex_user -> host . str , lex_user -> user . str , TRUE ) ;
 if ( ! acl_user ) {
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 rw_unlock ( & LOCK_grant ) ;
 my_error ( ER_NONEXISTING_GRANT , MYF ( 0 ) , lex_user -> user . str , lex_user -> host . str ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 Item_string * field = new Item_string ( "" , 0 , & my_charset_latin1 ) ;
 List < Item > field_list ;
 field -> name = buff ;
 field -> max_length = 1024 ;
 strxmov ( buff , "Grants for " , lex_user -> user . str , "@" , lex_user -> host . str , NullS ) ;
 field_list . push_back ( field ) ;
 if ( protocol -> send_fields ( & field_list , Protocol : : SEND_NUM_ROWS | Protocol : : SEND_EOF ) ) {
 VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 rw_unlock ( & LOCK_grant ) ;
 DBUG_RETURN ( TRUE ) ;
 }
 {
 String global ( buff , sizeof ( buff ) , system_charset_info ) ;
 global . length ( 0 ) ;
 global . append ( STRING_WITH_LEN ( "GRANT " ) ) ;
 want_access = acl_user -> access ;
 if ( test_all_bits ( want_access , ( GLOBAL_ACLS & ~ GRANT_ACL ) ) ) global . append ( STRING_WITH_LEN ( "ALL PRIVILEGES" ) ) ;
 else if ( ! ( want_access & ~ GRANT_ACL ) ) global . append ( STRING_WITH_LEN ( "USAGE" ) ) ;
 else {
 bool found = 0 ;
 ulong j , test_access = want_access & ~ GRANT_ACL ;
 for ( counter = 0 , j = SELECT_ACL ;
 j <= GLOBAL_ACLS ;
 counter ++ , j <<= 1 ) {
 if ( test_access & j ) {
 if ( found ) global . append ( STRING_WITH_LEN ( ", " ) ) ;
 found = 1 ;
 global . append ( command_array [ counter ] , command_lengths [ counter ] ) ;
 }
 }
 }
 global . append ( STRING_WITH_LEN ( " ON *.* TO '" ) ) ;
 global . append ( lex_user -> user . str , lex_user -> user . length , system_charset_info ) ;
 global . append ( STRING_WITH_LEN ( "'@'" ) ) ;
 global . append ( lex_user -> host . str , lex_user -> host . length , system_charset_info ) ;
 global . append ( '\'' ) ;
 if ( acl_user -> salt_len ) {
 global . append ( STRING_WITH_LEN ( " IDENTIFIED BY PASSWORD" ) ) ;
 if ( ( thd -> security_ctx -> master_access & SUPER_ACL ) == SUPER_ACL ) {
 char passwd_buff [ SCRAMBLED_PASSWORD_CHAR_LENGTH + 1 ] ;
 if ( acl_user -> salt_len == SCRAMBLE_LENGTH ) make_password_from_salt ( passwd_buff , acl_user -> salt ) ;
 else make_password_from_salt_323 ( passwd_buff , ( ulong * ) acl_user -> salt ) ;
 global . append ( " \'" ) ;
 global . append ( passwd_buff ) ;
 global . append ( '\'' ) ;
 }
 else global . append ( " <secret>" ) ;
 }
 if ( acl_user -> ssl_type == SSL_TYPE_ANY ) global . append ( STRING_WITH_LEN ( " REQUIRE SSL" ) ) ;
 else if ( acl_user -> ssl_type == SSL_TYPE_X509 ) global . append ( STRING_WITH_LEN ( " REQUIRE X509" ) ) ;
 else if ( acl_user -> ssl_type == SSL_TYPE_SPECIFIED ) {
 int ssl_options = 0 ;
 global . append ( STRING_WITH_LEN ( " REQUIRE " ) ) ;
 if ( acl_user -> x509_issuer ) {
 ssl_options ++ ;
 global . append ( STRING_WITH_LEN ( "ISSUER \'" ) ) ;
 global . append ( acl_user -> x509_issuer , strlen ( acl_user -> x509_issuer ) ) ;
 global . append ( '\'' ) ;
 }
 if ( acl_user -> x509_subject ) {
 if ( ssl_options ++ ) global . append ( ' ' ) ;
 global . append ( STRING_WITH_LEN ( "SUBJECT \'" ) ) ;
 global . append ( acl_user -> x509_subject , strlen ( acl_user -> x509_subject ) , system_charset_info ) ;
 global . append ( '\'' ) ;
 }
 if ( acl_user -> ssl_cipher ) {
 if ( ssl_options ++ ) global . append ( ' ' ) ;
 global . append ( STRING_WITH_LEN ( "CIPHER '" ) ) ;
 global . append ( acl_user -> ssl_cipher , strlen ( acl_user -> ssl_cipher ) , system_charset_info ) ;
 global . append ( '\'' ) ;
 }
 }
 if ( ( want_access & GRANT_ACL ) || ( acl_user -> user_resource . questions || acl_user -> user_resource . updates || acl_user -> user_resource . conn_per_hour || acl_user -> user_resource . user_conn ) ) {
 global . append ( STRING_WITH_LEN ( " WITH" ) ) ;
 if ( want_access & GRANT_ACL ) global . append ( STRING_WITH_LEN ( " GRANT OPTION" ) ) ;
 add_user_option ( & global , acl_user -> user_resource . questions , "MAX_QUERIES_PER_HOUR" ) ;
 add_user_option ( & global , acl_user -> user_resource . updates , "MAX_UPDATES_PER_HOUR" ) ;
 add_user_option ( & global , acl_user -> user_resource . conn_per_hour , "MAX_CONNECTIONS_PER_HOUR" ) ;
 add_user_option ( & global , acl_user -> user_resource . user_conn , "MAX_USER_CONNECTIONS" ) ;
 }
 protocol -> prepare_for_resend ( ) ;
 protocol -> store ( global . ptr ( ) , global . length ( ) , global . charset ( ) ) ;
 if ( protocol -> write ( ) ) {
 error = - 1 ;
 goto end ;
 }
 }
 for ( counter = 0 ;
 counter < acl_dbs . elements ;
 counter ++ ) {
 const char * user , * host ;
 acl_db = dynamic_element ( & acl_dbs , counter , ACL_DB * ) ;
 if ( ! ( user = acl_db -> user ) ) user = "" ;
 if ( ! ( host = acl_db -> host . hostname ) ) host = "" ;
 if ( ! strcmp ( lex_user -> user . str , user ) && ! my_strcasecmp ( system_charset_info , lex_user -> host . str , host ) ) {
 want_access = acl_db -> access ;
 if ( want_access ) {
 String db ( buff , sizeof ( buff ) , system_charset_info ) ;
 db . length ( 0 ) ;
 db . append ( STRING_WITH_LEN ( "GRANT " ) ) ;
 if ( test_all_bits ( want_access , ( DB_ACLS & ~ GRANT_ACL ) ) ) db . append ( STRING_WITH_LEN ( "ALL PRIVILEGES" ) ) ;
 else if ( ! ( want_access & ~ GRANT_ACL ) ) db . append ( STRING_WITH_LEN ( "USAGE" ) ) ;
 else {
 int found = 0 , cnt ;
 ulong j , test_access = want_access & ~ GRANT_ACL ;
 for ( cnt = 0 , j = SELECT_ACL ;
 j <= DB_ACLS ;
 cnt ++ , j <<= 1 ) {
 if ( test_access & j ) {
 if ( found ) db . append ( STRING_WITH_LEN ( ", " ) ) ;
 found = 1 ;
 db . append ( command_array [ cnt ] , command_lengths [ cnt ] ) ;
 }
 }
 }
 db . append ( STRING_WITH_LEN ( " ON " ) ) ;
 append_identifier ( thd , & db , acl_db -> db , strlen ( acl_db -> db ) ) ;
 db . append ( STRING_WITH_LEN ( ".* TO '" ) ) ;
 db . append ( lex_user -> user . str , lex_user -> user . length , system_charset_info ) ;
 db . append ( STRING_WITH_LEN ( "'@'" ) ) ;
 db . append ( host , strlen ( host ) , system_charset_info ) ;
 db . append ( '\'' ) ;
 if ( want_access & GRANT_ACL ) db . append ( STRING_WITH_LEN ( " WITH GRANT OPTION" ) ) ;
 protocol -> prepare_for_resend ( ) ;
 protocol -> store ( db . ptr ( ) , db . length ( ) , db . charset ( ) ) ;
 if ( protocol -> write ( ) ) {
 error = - 1 ;
 goto end ;
 }
 }
 }
 }
 for ( index = 0 ;
 index < column_priv_hash . records ;
 index ++ ) {
 const char * user , * host ;
 GRANT_TABLE * grant_table = ( GRANT_TABLE * ) hash_element ( & column_priv_hash , index ) ;
 if ( ! ( user = grant_table -> user ) ) user = "" ;
 if ( ! ( host = grant_table -> host . hostname ) ) host = "" ;
 if ( ! strcmp ( lex_user -> user . str , user ) && ! my_strcasecmp ( system_charset_info , lex_user -> host . str , host ) ) {
 ulong table_access = grant_table -> privs ;
 if ( ( table_access | grant_table -> cols ) != 0 ) {
 String global ( buff , sizeof ( buff ) , system_charset_info ) ;
 ulong test_access = ( table_access | grant_table -> cols ) & ~ GRANT_ACL ;
 global . length ( 0 ) ;
 global . append ( STRING_WITH_LEN ( "GRANT " ) ) ;
 if ( test_all_bits ( table_access , ( TABLE_ACLS & ~ GRANT_ACL ) ) ) global . append ( STRING_WITH_LEN ( "ALL PRIVILEGES" ) ) ;
 else if ( ! test_access ) global . append ( STRING_WITH_LEN ( "USAGE" ) ) ;
 else {
 int found = 0 ;
 ulong j ;
 for ( counter = 0 , j = SELECT_ACL ;
 j <= TABLE_ACLS ;
 counter ++ , j <<= 1 ) {
 if ( test_access & j ) {
 if ( found ) global . append ( STRING_WITH_LEN ( ", " ) ) ;
 found = 1 ;
 global . append ( command_array [ counter ] , command_lengths [ counter ] ) ;
 if ( grant_table -> cols ) {
 uint found_col = 0 ;
 for ( uint col_index = 0 ;
 col_index < grant_table -> hash_columns . records ;
 col_index ++ ) {
 GRANT_COLUMN * grant_column = ( GRANT_COLUMN * ) hash_element ( & grant_table -> hash_columns , col_index ) ;
 if ( grant_column -> rights & j ) {
 if ( ! found_col ) {
 found_col = 1 ;
 if ( table_access & j ) {
 global . append ( STRING_WITH_LEN ( ", " ) ) ;
 global . append ( command_array [ counter ] , command_lengths [ counter ] ) ;
 }
 global . append ( STRING_WITH_LEN ( " (" ) ) ;
 }
 else global . append ( STRING_WITH_LEN ( ", " ) ) ;
 global . append ( grant_column -> column , grant_column -> key_length , system_charset_info ) ;
 }
 }
 if ( found_col ) global . append ( ')' ) ;
 }
 }
 }
 }
 global . append ( STRING_WITH_LEN ( " ON " ) ) ;
 append_identifier ( thd , & global , grant_table -> db , strlen ( grant_table -> db ) ) ;
 global . append ( '.' ) ;
 append_identifier ( thd , & global , grant_table -> tname , strlen ( grant_table -> tname ) ) ;
 global . append ( STRING_WITH_LEN ( " TO '" ) ) ;
 global . append ( lex_user -> user . str , lex_user -> user . length , system_charset_info ) ;
 global . append ( STRING_WITH_LEN ( "'@'" ) ) ;
 global . append ( host , strlen ( host ) , system_charset_info ) ;
 global . append ( '\'' ) ;
 if ( table_access & GRANT_ACL ) global . append ( STRING_WITH_LEN ( " WITH GRANT OPTION" ) ) ;
 protocol -> prepare_for_resend ( ) ;
 protocol -> store ( global . ptr ( ) , global . length ( ) , global . charset ( ) ) ;
 if ( protocol -> write ( ) ) {
 error = - 1 ;
 break ;
 }
 }
 }
 }
 if ( show_routine_grants ( thd , lex_user , & proc_priv_hash , STRING_WITH_LEN ( "PROCEDURE" ) , buff , sizeof ( buff ) ) ) {
 error = - 1 ;
 goto end ;
 }
 if ( show_routine_grants ( thd , lex_user , & func_priv_hash , STRING_WITH_LEN ( "FUNCTION" ) , buff , sizeof ( buff ) ) ) {
 error = - 1 ;
 goto end ;
 }
 end : VOID ( pthread_mutex_unlock ( & acl_cache -> lock ) ) ;
 rw_unlock ( & LOCK_grant ) ;
 my_eof ( thd ) ;
 DBUG_RETURN ( error ) ;
 }