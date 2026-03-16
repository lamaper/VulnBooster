static void sapi_uwsgi_register_variables ( zval * track_vars_array TSRMLS_DC ) {
 int i ;
 struct wsgi_request * wsgi_req = ( struct wsgi_request * ) SG ( server_context ) ;
 php_import_environment_variables ( track_vars_array TSRMLS_CC ) ;
 if ( uphp . server_software ) {
 if ( ! uphp . server_software_len ) uphp . server_software_len = strlen ( uphp . server_software ) ;
 php_register_variable_safe ( "SERVER_SOFTWARE" , uphp . server_software , uphp . server_software_len , track_vars_array TSRMLS_CC ) ;
 }
 else {
 php_register_variable_safe ( "SERVER_SOFTWARE" , "uWSGI" , 5 , track_vars_array TSRMLS_CC ) ;
 }
 for ( i = 0 ;
 i < wsgi_req -> var_cnt ;
 i += 2 ) {
 php_register_variable_safe ( estrndup ( wsgi_req -> hvec [ i ] . iov_base , wsgi_req -> hvec [ i ] . iov_len ) , wsgi_req -> hvec [ i + 1 ] . iov_base , wsgi_req -> hvec [ i + 1 ] . iov_len , track_vars_array TSRMLS_CC ) ;
 }
 php_register_variable_safe ( "PATH_INFO" , wsgi_req -> path_info , wsgi_req -> path_info_len , track_vars_array TSRMLS_CC ) ;
 if ( wsgi_req -> query_string_len > 0 ) {
 php_register_variable_safe ( "QUERY_STRING" , wsgi_req -> query_string , wsgi_req -> query_string_len , track_vars_array TSRMLS_CC ) ;
 }
 php_register_variable_safe ( "SCRIPT_NAME" , wsgi_req -> script_name , wsgi_req -> script_name_len , track_vars_array TSRMLS_CC ) ;
 php_register_variable_safe ( "SCRIPT_FILENAME" , wsgi_req -> file , wsgi_req -> file_len , track_vars_array TSRMLS_CC ) ;
 php_register_variable_safe ( "DOCUMENT_ROOT" , wsgi_req -> document_root , wsgi_req -> document_root_len , track_vars_array TSRMLS_CC ) ;
 if ( wsgi_req -> path_info_len ) {
 char * path_translated = ecalloc ( 1 , wsgi_req -> file_len + wsgi_req -> path_info_len + 1 ) ;
 memcpy ( path_translated , wsgi_req -> file , wsgi_req -> file_len ) ;
 memcpy ( path_translated + wsgi_req -> file_len , wsgi_req -> path_info , wsgi_req -> path_info_len ) ;
 php_register_variable_safe ( "PATH_TRANSLATED" , path_translated , wsgi_req -> file_len + wsgi_req -> path_info_len , track_vars_array TSRMLS_CC ) ;
 }
 else {
 php_register_variable_safe ( "PATH_TRANSLATED" , "" , 0 , track_vars_array TSRMLS_CC ) ;
 }
 php_register_variable_safe ( "PHP_SELF" , wsgi_req -> script_name , wsgi_req -> script_name_len , track_vars_array TSRMLS_CC ) ;
 struct uwsgi_string_list * usl = uphp . vars ;
 while ( usl ) {
 char * equal = strchr ( usl -> value , '=' ) ;
 if ( equal ) {
 php_register_variable_safe ( estrndup ( usl -> value , equal - usl -> value ) , equal + 1 , strlen ( equal + 1 ) , track_vars_array TSRMLS_CC ) ;
 }
 usl = usl -> next ;
 }
 }