int connect_n_handle_errors ( struct st_command * command , MYSQL * con , const char * host , const char * user , const char * pass , const char * db , int port , const char * sock ) {
 DYNAMIC_STRING * ds ;
 int failed_attempts = 0 ;
 ds = & ds_res ;
 if ( command -> expected_errors . count > 0 && ! disable_query_log ) {
 dynstr_append_mem ( ds , "connect(" , 8 ) ;
 replace_dynstr_append ( ds , host ) ;
 dynstr_append_mem ( ds , "," , 1 ) ;
 replace_dynstr_append ( ds , user ) ;
 dynstr_append_mem ( ds , "," , 1 ) ;
 replace_dynstr_append ( ds , pass ) ;
 dynstr_append_mem ( ds , "," , 1 ) ;
 if ( db ) replace_dynstr_append ( ds , db ) ;
 dynstr_append_mem ( ds , "," , 1 ) ;
 replace_dynstr_append_uint ( ds , port ) ;
 dynstr_append_mem ( ds , "," , 1 ) ;
 if ( sock ) replace_dynstr_append ( ds , sock ) ;
 dynstr_append_mem ( ds , ")" , 1 ) ;
 dynstr_append_mem ( ds , delimiter , delimiter_length ) ;
 dynstr_append_mem ( ds , "\n" , 1 ) ;
 }
 if ( ! disable_connect_log && ! disable_query_log ) {
 replace_dynstr_append ( ds , command -> query ) ;
 dynstr_append_mem ( ds , ";
\n" , 2 ) ;
 }
 while ( ! mysql_real_connect ( con , host , user , pass , db , port , sock ? sock : 0 , CLIENT_MULTI_STATEMENTS ) ) {
 if ( ( ( mysql_errno ( con ) == ER_TOO_MANY_USER_CONNECTIONS ) || ( mysql_errno ( con ) == ER_USER_LIMIT_REACHED ) ) && ( failed_attempts ++ < opt_max_connect_retries ) ) {
 int i ;
 i = match_expected_error ( command , mysql_errno ( con ) , mysql_sqlstate ( con ) ) ;
 if ( i >= 0 ) goto do_handle_error ;
 my_sleep ( connection_retry_sleep ) ;
 continue ;
 }
 do_handle_error : var_set_errno ( mysql_errno ( con ) ) ;
 handle_error ( command , mysql_errno ( con ) , mysql_error ( con ) , mysql_sqlstate ( con ) , ds ) ;
 return 0 ;
 }
 var_set_errno ( 0 ) ;
 handle_no_error ( command ) ;
 revert_properties ( ) ;
 return 1 ;
 }