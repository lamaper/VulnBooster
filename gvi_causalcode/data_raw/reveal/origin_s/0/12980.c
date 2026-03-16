static int replace_user_table ( THD * thd , TABLE * table , const LEX_USER & combo , ulong rights , bool revoke_grant , bool can_create_user , bool no_auto_create ) {
 int error = - 1 ;
 bool old_row_exists = 0 ;
 const char * password = "" ;
 uint password_len = 0 ;
 char what = ( revoke_grant ) ? 'N' : 'Y' ;
 uchar user_key [ MAX_KEY_LENGTH ] ;
 LEX * lex = thd -> lex ;
 DBUG_ENTER ( "replace_user_table" ) ;
 safe_mutex_assert_owner ( & acl_cache -> lock ) ;
 if ( combo . password . str && combo . password . str [ 0 ] ) {
 if ( combo . password . length != SCRAMBLED_PASSWORD_CHAR_LENGTH && combo . password . length != SCRAMBLED_PASSWORD_CHAR_LENGTH_323 ) {
 my_error ( ER_PASSWD_LENGTH , MYF ( 0 ) , SCRAMBLED_PASSWORD_CHAR_LENGTH ) ;
 DBUG_RETURN ( - 1 ) ;
 }
 password_len = combo . password . length ;
 password = combo . password . str ;
 }
 table -> use_all_columns ( ) ;
 table -> field [ 0 ] -> store ( combo . host . str , combo . host . length , system_charset_info ) ;
 table -> field [ 1 ] -> store ( combo . user . str , combo . user . length , system_charset_info ) ;
 key_copy ( user_key , table -> record [ 0 ] , table -> key_info , table -> key_info -> key_length ) ;
 if ( table -> file -> index_read_idx_map ( table -> record [ 0 ] , 0 , user_key , HA_WHOLE_KEY , HA_READ_KEY_EXACT ) ) {
 if ( what == 'N' ) {
 my_error ( ER_NONEXISTING_GRANT , MYF ( 0 ) , combo . user . str , combo . host . str ) ;
 goto end ;
 }
 else if ( ! password_len && no_auto_create ) {
 my_error ( ER_PASSWORD_NO_MATCH , MYF ( 0 ) ) ;
 goto end ;
 }
 else if ( ! can_create_user ) {
 my_error ( ER_CANT_CREATE_USER_WITH_GRANT , MYF ( 0 ) ) ;
 goto end ;
 }
 old_row_exists = 0 ;
 restore_record ( table , s -> default_values ) ;
 table -> field [ 0 ] -> store ( combo . host . str , combo . host . length , system_charset_info ) ;
 table -> field [ 1 ] -> store ( combo . user . str , combo . user . length , system_charset_info ) ;
 table -> field [ 2 ] -> store ( password , password_len , system_charset_info ) ;
 }
 else {
 old_row_exists = 1 ;
 store_record ( table , record [ 1 ] ) ;
 if ( combo . password . str ) table -> field [ 2 ] -> store ( password , password_len , system_charset_info ) ;
 else if ( ! rights && ! revoke_grant && lex -> ssl_type == SSL_TYPE_NOT_SPECIFIED && ! lex -> mqh . specified_limits ) {
 DBUG_RETURN ( 0 ) ;
 }
 }
 Field * * tmp_field ;
 ulong priv ;
 uint next_field ;
 for ( tmp_field = table -> field + 3 , priv = SELECT_ACL ;
 * tmp_field && ( * tmp_field ) -> real_type ( ) == MYSQL_TYPE_ENUM && ( ( Field_enum * ) ( * tmp_field ) ) -> typelib -> count == 2 ;
 tmp_field ++ , priv <<= 1 ) {
 if ( priv & rights ) ( * tmp_field ) -> store ( & what , 1 , & my_charset_latin1 ) ;
 }
 rights = get_access ( table , 3 , & next_field ) ;
 DBUG_PRINT ( "info" , ( "table fields: %d" , table -> s -> fields ) ) ;
 if ( table -> s -> fields >= 31 ) {
 switch ( lex -> ssl_type ) {
 case SSL_TYPE_ANY : table -> field [ next_field ] -> store ( STRING_WITH_LEN ( "ANY" ) , & my_charset_latin1 ) ;
 table -> field [ next_field + 1 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 2 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 3 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 break ;
 case SSL_TYPE_X509 : table -> field [ next_field ] -> store ( STRING_WITH_LEN ( "X509" ) , & my_charset_latin1 ) ;
 table -> field [ next_field + 1 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 2 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 3 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 break ;
 case SSL_TYPE_SPECIFIED : table -> field [ next_field ] -> store ( STRING_WITH_LEN ( "SPECIFIED" ) , & my_charset_latin1 ) ;
 table -> field [ next_field + 1 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 2 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 3 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 if ( lex -> ssl_cipher ) table -> field [ next_field + 1 ] -> store ( lex -> ssl_cipher , strlen ( lex -> ssl_cipher ) , system_charset_info ) ;
 if ( lex -> x509_issuer ) table -> field [ next_field + 2 ] -> store ( lex -> x509_issuer , strlen ( lex -> x509_issuer ) , system_charset_info ) ;
 if ( lex -> x509_subject ) table -> field [ next_field + 3 ] -> store ( lex -> x509_subject , strlen ( lex -> x509_subject ) , system_charset_info ) ;
 break ;
 case SSL_TYPE_NOT_SPECIFIED : break ;
 case SSL_TYPE_NONE : table -> field [ next_field ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 1 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 2 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 table -> field [ next_field + 3 ] -> store ( "" , 0 , & my_charset_latin1 ) ;
 break ;
 }
 next_field += 4 ;
 USER_RESOURCES mqh = lex -> mqh ;
 if ( mqh . specified_limits & USER_RESOURCES : : QUERIES_PER_HOUR ) table -> field [ next_field ] -> store ( ( longlong ) mqh . questions , TRUE ) ;
 if ( mqh . specified_limits & USER_RESOURCES : : UPDATES_PER_HOUR ) table -> field [ next_field + 1 ] -> store ( ( longlong ) mqh . updates , TRUE ) ;
 if ( mqh . specified_limits & USER_RESOURCES : : CONNECTIONS_PER_HOUR ) table -> field [ next_field + 2 ] -> store ( ( longlong ) mqh . conn_per_hour , TRUE ) ;
 if ( table -> s -> fields >= 36 && ( mqh . specified_limits & USER_RESOURCES : : USER_CONNECTIONS ) ) table -> field [ next_field + 3 ] -> store ( ( longlong ) mqh . user_conn , TRUE ) ;
 mqh_used = mqh_used || mqh . questions || mqh . updates || mqh . conn_per_hour ;
 }
 if ( old_row_exists ) {
 if ( cmp_record ( table , record [ 1 ] ) ) {
 if ( ( error = table -> file -> ha_update_row ( table -> record [ 1 ] , table -> record [ 0 ] ) ) && error != HA_ERR_RECORD_IS_THE_SAME ) {
 table -> file -> print_error ( error , MYF ( 0 ) ) ;
 error = - 1 ;
 goto end ;
 }
 else error = 0 ;
 }
 }
 else if ( ( error = table -> file -> ha_write_row ( table -> record [ 0 ] ) ) ) {
 if ( table -> file -> is_fatal_error ( error , HA_CHECK_DUP ) ) {
 table -> file -> print_error ( error , MYF ( 0 ) ) ;
 error = - 1 ;
 goto end ;
 }
 }
 error = 0 ;
 end : if ( ! error ) {
 acl_cache -> clear ( 1 ) ;
 if ( old_row_exists ) acl_update_user ( combo . user . str , combo . host . str , combo . password . str , password_len , lex -> ssl_type , lex -> ssl_cipher , lex -> x509_issuer , lex -> x509_subject , & lex -> mqh , rights ) ;
 else acl_insert_user ( combo . user . str , combo . host . str , password , password_len , lex -> ssl_type , lex -> ssl_cipher , lex -> x509_issuer , lex -> x509_subject , & lex -> mqh , rights ) ;
 }
 DBUG_RETURN ( error ) ;
 }