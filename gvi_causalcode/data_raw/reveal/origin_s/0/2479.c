int check_change_password ( THD * thd , const char * host , const char * user , char * new_password , uint new_password_len ) {
 if ( ! initialized ) {
 my_error ( ER_OPTION_PREVENTS_STATEMENT , MYF ( 0 ) , "--skip-grant-tables" ) ;
 return ( 1 ) ;
 }
 if ( ! thd -> slave_thread && ( strcmp ( thd -> security_ctx -> user , user ) || my_strcasecmp ( system_charset_info , host , thd -> security_ctx -> priv_host ) ) ) {
 if ( check_access ( thd , UPDATE_ACL , "mysql" , 0 , 1 , 0 , 0 ) ) return ( 1 ) ;
 }
 if ( ! thd -> slave_thread && ! thd -> security_ctx -> user [ 0 ] ) {
 my_message ( ER_PASSWORD_ANONYMOUS_USER , ER ( ER_PASSWORD_ANONYMOUS_USER ) , MYF ( 0 ) ) ;
 return ( 1 ) ;
 }
 size_t len = strlen ( new_password ) ;
 if ( len && len != SCRAMBLED_PASSWORD_CHAR_LENGTH && len != SCRAMBLED_PASSWORD_CHAR_LENGTH_323 ) {
 my_error ( ER_PASSWD_LENGTH , MYF ( 0 ) , SCRAMBLED_PASSWORD_CHAR_LENGTH ) ;
 return - 1 ;
 }
 return ( 0 ) ;
 }