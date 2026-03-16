static int sapi_uwsgi_read_post ( char * buffer , uint count_bytes TSRMLS_DC ) # endif {
 uint read_bytes = 0 ;
 struct wsgi_request * wsgi_req = ( struct wsgi_request * ) SG ( server_context ) ;
 count_bytes = MIN ( count_bytes , wsgi_req -> post_cl - SG ( read_post_bytes ) ) ;
 while ( read_bytes < count_bytes ) {
 ssize_t rlen = 0 ;
 char * buf = uwsgi_request_body_read ( wsgi_req , count_bytes - read_bytes , & rlen ) ;
 if ( buf == uwsgi . empty ) break ;
 if ( buf ) {
 memcpy ( buffer , buf , rlen ) ;
 read_bytes += rlen ;
 continue ;
 }
 break ;
 }
 return read_bytes ;
 }