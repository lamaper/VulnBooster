static my_bool acl_load ( THD * thd , TABLE_LIST * tables ) {
 TABLE * table ;
 READ_RECORD read_record_info ;
 my_bool return_val = TRUE ;
 bool check_no_resolve = specialflag & SPECIAL_NO_RESOLVE ;
 char tmp_name [ NAME_LEN + 1 ] ;
 int password_length ;
 ulong old_sql_mode = thd -> variables . sql_mode ;
 DBUG_ENTER ( "acl_load" ) ;
 thd -> variables . sql_mode &= ~ MODE_PAD_CHAR_TO_FULL_LENGTH ;
 grant_version ++ ;
 acl_cache -> clear ( 1 ) ;
 init_sql_alloc ( & mem , ACL_ALLOC_BLOCK_SIZE , 0 ) ;
 init_read_record ( & read_record_info , thd , table = tables [ 0 ] . table , NULL , 1 , 0 , FALSE ) ;
 table -> use_all_columns ( ) ;
 VOID ( my_init_dynamic_array ( & acl_hosts , sizeof ( ACL_HOST ) , 20 , 50 ) ) ;
 while ( ! ( read_record_info . read_record ( & read_record_info ) ) ) {
 ACL_HOST host ;
 update_hostname ( & host . host , get_field ( & mem , table -> field [ 0 ] ) ) ;
 host . db = get_field ( & mem , table -> field [ 1 ] ) ;
 if ( lower_case_table_names && host . db ) {
 ( void ) strmov ( tmp_name , host . db ) ;
 my_casedn_str ( files_charset_info , host . db ) ;
 if ( strcmp ( host . db , tmp_name ) != 0 ) sql_print_warning ( "'host' entry '%s|%s' had database in mixed " "case that has been forced to lowercase because " "lower_case_table_names is set. It will not be " "possible to remove this privilege using REVOKE." , host . host . hostname ? host . host . hostname : "" , host . db ? host . db : "" ) ;
 }
 host . access = get_access ( table , 2 ) ;
 host . access = fix_rights_for_db ( host . access ) ;
 host . sort = get_sort ( 2 , host . host . hostname , host . db ) ;
 if ( check_no_resolve && hostname_requires_resolving ( host . host . hostname ) ) {
 sql_print_warning ( "'host' entry '%s|%s' " "ignored in --skip-name-resolve mode." , host . host . hostname ? host . host . hostname : "" , host . db ? host . db : "" ) ;
 continue ;
 }

 if ( host . access & CREATE_ACL ) host . access |= REFERENCES_ACL | INDEX_ACL | ALTER_ACL | CREATE_TMP_ACL ;
 }

 }
 my_qsort ( ( uchar * ) dynamic_element ( & acl_hosts , 0 , ACL_HOST * ) , acl_hosts . elements , sizeof ( ACL_HOST ) , ( qsort_cmp ) acl_compare ) ;
 end_read_record ( & read_record_info ) ;
 freeze_size ( & acl_hosts ) ;
 init_read_record ( & read_record_info , thd , table = tables [ 1 ] . table , NULL , 1 , 0 , FALSE ) ;
 table -> use_all_columns ( ) ;
 VOID ( my_init_dynamic_array ( & acl_users , sizeof ( ACL_USER ) , 50 , 100 ) ) ;
 password_length = table -> field [ 2 ] -> field_length / table -> field [ 2 ] -> charset ( ) -> mbmaxlen ;
 if ( password_length < SCRAMBLED_PASSWORD_CHAR_LENGTH_323 ) {
 sql_print_error ( "Fatal error: mysql.user table is damaged or in " "unsupported 3.20 format." ) ;
 goto end ;
 }
 DBUG_PRINT ( "info" , ( "user table fields: %d, password length: %d" , table -> s -> fields , password_length ) ) ;
 pthread_mutex_lock ( & LOCK_global_system_variables ) ;
 if ( password_length < SCRAMBLED_PASSWORD_CHAR_LENGTH ) {
 if ( opt_secure_auth ) {
 pthread_mutex_unlock ( & LOCK_global_system_variables ) ;
 sql_print_error ( "Fatal error: mysql.user table is in old format, " "but server started with --secure-auth option." ) ;
 goto end ;
 }
 sys_old_passwords . after_update = restrict_update_of_old_passwords_var ;
 if ( global_system_variables . old_passwords ) pthread_mutex_unlock ( & LOCK_global_system_variables ) ;
 else {
 global_system_variables . old_passwords = 1 ;
 pthread_mutex_unlock ( & LOCK_global_system_variables ) ;
 sql_print_warning ( "mysql.user table is not updated to new password format;
 " "Disabling new password usage until " "mysql_fix_privilege_tables is run" ) ;
 }
 thd -> variables . old_passwords = 1 ;
 }
 else {
 sys_old_passwords . after_update = 0 ;
 pthread_mutex_unlock ( & LOCK_global_system_variables ) ;
 }
 allow_all_hosts = 0 ;
 while ( ! ( read_record_info . read_record ( & read_record_info ) ) ) {
 ACL_USER user ;
 update_hostname ( & user . host , get_field ( & mem , table -> field [ 0 ] ) ) ;
 user . user = get_field ( & mem , table -> field [ 1 ] ) ;
 if ( check_no_resolve && hostname_requires_resolving ( user . host . hostname ) ) {
 sql_print_warning ( "'user' entry '%s@%s' " "ignored in --skip-name-resolve mode." , user . user ? user . user : "" , user . host . hostname ? user . host . hostname : "" ) ;
 continue ;
 }
 const char * password = get_field ( thd -> mem_root , table -> field [ 2 ] ) ;
 uint password_len = password ? strlen ( password ) : 0 ;
 set_user_salt ( & user , password , password_len ) ;
 if ( user . salt_len == 0 && password_len != 0 ) {
 switch ( password_len ) {
 case 45 : sql_print_warning ( "Found 4.1 style password for user '%s@%s'. " "Ignoring user. " "You should change password for this user." , user . user ? user . user : "" , user . host . hostname ? user . host . hostname : "" ) ;
 break ;
 default : sql_print_warning ( "Found invalid password for user: '%s@%s';
 " "Ignoring user" , user . user ? user . user : "" , user . host . hostname ? user . host . hostname : "" ) ;
 break ;
 }
 }
 else {
 uint next_field ;
 user . access = get_access ( table , 3 , & next_field ) & GLOBAL_ACLS ;
 if ( table -> s -> fields <= 31 && ( user . access & CREATE_ACL ) ) user . access |= ( CREATE_VIEW_ACL | SHOW_VIEW_ACL ) ;
 if ( table -> s -> fields <= 33 && ( user . access & CREATE_ACL ) ) user . access |= CREATE_PROC_ACL ;
 if ( table -> s -> fields <= 33 && ( user . access & ALTER_ACL ) ) user . access |= ALTER_PROC_ACL ;
 if ( table -> s -> fields <= 36 && ( user . access & GRANT_ACL ) ) user . access |= CREATE_USER_ACL ;
 if ( table -> s -> fields <= 37 && ( user . access & SUPER_ACL ) ) user . access |= EVENT_ACL ;
 if ( table -> s -> fields <= 38 && ( user . access & SUPER_ACL ) ) user . access |= TRIGGER_ACL ;
 user . sort = get_sort ( 2 , user . host . hostname , user . user ) ;
 user . hostname_length = ( user . host . hostname ? ( uint ) strlen ( user . host . hostname ) : 0 ) ;
 if ( table -> s -> fields >= 31 ) {
 char * ssl_type = get_field ( thd -> mem_root , table -> field [ next_field ++ ] ) ;
 if ( ! ssl_type ) user . ssl_type = SSL_TYPE_NONE ;
 else if ( ! strcmp ( ssl_type , "ANY" ) ) user . ssl_type = SSL_TYPE_ANY ;
 else if ( ! strcmp ( ssl_type , "X509" ) ) user . ssl_type = SSL_TYPE_X509 ;
 else user . ssl_type = SSL_TYPE_SPECIFIED ;
 user . ssl_cipher = get_field ( & mem , table -> field [ next_field ++ ] ) ;
 user . x509_issuer = get_field ( & mem , table -> field [ next_field ++ ] ) ;
 user . x509_subject = get_field ( & mem , table -> field [ next_field ++ ] ) ;
 char * ptr = get_field ( thd -> mem_root , table -> field [ next_field ++ ] ) ;
 user . user_resource . questions = ptr ? atoi ( ptr ) : 0 ;
 ptr = get_field ( thd -> mem_root , table -> field [ next_field ++ ] ) ;
 user . user_resource . updates = ptr ? atoi ( ptr ) : 0 ;
 ptr = get_field ( thd -> mem_root , table -> field [ next_field ++ ] ) ;
 user . user_resource . conn_per_hour = ptr ? atoi ( ptr ) : 0 ;
 if ( user . user_resource . questions || user . user_resource . updates || user . user_resource . conn_per_hour ) mqh_used = 1 ;
 if ( table -> s -> fields >= 36 ) {
 ptr = get_field ( thd -> mem_root , table -> field [ next_field ++ ] ) ;
 user . user_resource . user_conn = ptr ? atoi ( ptr ) : 0 ;
 }
 else user . user_resource . user_conn = 0 ;
 }
 else {
 user . ssl_type = SSL_TYPE_NONE ;
 bzero ( ( char * ) & ( user . user_resource ) , sizeof ( user . user_resource ) ) ;

 if ( user . access & CREATE_ACL ) user . access |= REFERENCES_ACL | INDEX_ACL | ALTER_ACL ;
 }
 user . access |= LOCK_TABLES_ACL | CREATE_TMP_ACL | SHOW_DB_ACL ;
 if ( user . access & FILE_ACL ) user . access |= REPL_CLIENT_ACL | REPL_SLAVE_ACL ;
 if ( user . access & PROCESS_ACL ) user . access |= SUPER_ACL | EXECUTE_ACL ;

 VOID ( push_dynamic ( & acl_users , ( uchar * ) & user ) ) ;
 if ( ! user . host . hostname || ( user . host . hostname [ 0 ] == wild_many && ! user . host . hostname [ 1 ] ) ) allow_all_hosts = 1 ;
 }
 }
 my_qsort ( ( uchar * ) dynamic_element ( & acl_users , 0 , ACL_USER * ) , acl_users . elements , sizeof ( ACL_USER ) , ( qsort_cmp ) acl_compare ) ;
 end_read_record ( & read_record_info ) ;
 freeze_size ( & acl_users ) ;
 init_read_record ( & read_record_info , thd , table = tables [ 2 ] . table , NULL , 1 , 0 , FALSE ) ;
 table -> use_all_columns ( ) ;
 VOID ( my_init_dynamic_array ( & acl_dbs , sizeof ( ACL_DB ) , 50 , 100 ) ) ;
 while ( ! ( read_record_info . read_record ( & read_record_info ) ) ) {
 ACL_DB db ;
 update_hostname ( & db . host , get_field ( & mem , table -> field [ MYSQL_DB_FIELD_HOST ] ) ) ;
 db . db = get_field ( & mem , table -> field [ MYSQL_DB_FIELD_DB ] ) ;
 if ( ! db . db ) {
 sql_print_warning ( "Found an entry in the 'db' table with empty database name;
 Skipped" ) ;
 continue ;
 }
 db . user = get_field ( & mem , table -> field [ MYSQL_DB_FIELD_USER ] ) ;
 if ( check_no_resolve && hostname_requires_resolving ( db . host . hostname ) ) {
 sql_print_warning ( "'db' entry '%s %s@%s' " "ignored in --skip-name-resolve mode." , db . db , db . user ? db . user : "" , db . host . hostname ? db . host . hostname : "" ) ;
 continue ;
 }
 db . access = get_access ( table , 3 ) ;
 db . access = fix_rights_for_db ( db . access ) ;
 if ( lower_case_table_names ) {
 ( void ) strmov ( tmp_name , db . db ) ;
 my_casedn_str ( files_charset_info , db . db ) ;
 if ( strcmp ( db . db , tmp_name ) != 0 ) {
 sql_print_warning ( "'db' entry '%s %s@%s' had database in mixed " "case that has been forced to lowercase because " "lower_case_table_names is set. It will not be " "possible to remove this privilege using REVOKE." , db . db , db . user ? db . user : "" , db . host . hostname ? db . host . hostname : "" ) ;
 }
 }
 db . sort = get_sort ( 3 , db . host . hostname , db . db , db . user ) ;

 if ( db . access & CREATE_ACL ) db . access |= REFERENCES_ACL | INDEX_ACL | ALTER_ACL ;
 }

 }
 my_qsort ( ( uchar * ) dynamic_element ( & acl_dbs , 0 , ACL_DB * ) , acl_dbs . elements , sizeof ( ACL_DB ) , ( qsort_cmp ) acl_compare ) ;
 end_read_record ( & read_record_info ) ;
 freeze_size ( & acl_dbs ) ;
 init_check_host ( ) ;
 initialized = 1 ;
 return_val = FALSE ;
 end : thd -> variables . sql_mode = old_sql_mode ;
 DBUG_RETURN ( return_val ) ;
 }