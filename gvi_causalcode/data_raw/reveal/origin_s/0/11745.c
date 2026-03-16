static int sapi_uwsgi_ub_write ( const char * str , uint str_length TSRMLS_DC ) # endif {
 struct wsgi_request * wsgi_req = ( struct wsgi_request * ) SG ( server_context ) ;
 uwsgi_response_write_body_do ( wsgi_req , ( char * ) str , str_length ) ;
 if ( wsgi_req -> write_errors > uwsgi . write_errors_tolerance ) {
 php_handle_aborted_connection ( ) ;
 return - 1 ;
 }
 return str_length ;
 }