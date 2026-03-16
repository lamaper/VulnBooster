static char * sapi_uwsgi_read_cookies ( TSRMLS_D ) {
 uint16_t len = 0 ;
 struct wsgi_request * wsgi_req = ( struct wsgi_request * ) SG ( server_context ) ;
 char * cookie = uwsgi_get_var ( wsgi_req , ( char * ) "HTTP_COOKIE" , 11 , & len ) ;
 if ( cookie ) {
 return estrndup ( cookie , len ) ;
 }
 return NULL ;
 }