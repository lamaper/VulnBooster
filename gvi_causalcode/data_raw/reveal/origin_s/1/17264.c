static void evhttp_handle_request ( struct evhttp_request * req , void * arg ) {
 struct evhttp * http = arg ;
 struct evhttp_cb * cb = NULL ;
 if ( req -> uri == NULL ) {
 evhttp_send_error ( req , HTTP_BADREQUEST , "Bad Request" ) ;
 return ;
 }
 if ( ( cb = evhttp_dispatch_callback ( & http -> callbacks , req ) ) != NULL ) {
 ( * cb -> cb ) ( req , cb -> cbarg ) ;
 return ;
 }
 if ( http -> gencb ) {
 ( * http -> gencb ) ( req , http -> gencbarg ) ;
 return ;
 }
 else {

 struct evbuffer * buf = evbuffer_new ( ) ;
 evhttp_response_code ( req , HTTP_NOTFOUND , "Not Found" ) ;
 evbuffer_add_printf ( buf , ERR_FORMAT , escaped_html ) ;
 free ( escaped_html ) ;
 evhttp_send_page ( req , buf ) ;
 evbuffer_free ( buf ) ;

 }