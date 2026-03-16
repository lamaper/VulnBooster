static void evhttp_handle_request ( struct evhttp_request * req , void * arg ) {
 struct evhttp * http = arg ;
 struct evhttp_cb * cb = NULL ;
 event_debug ( ( "%s: req->uri=%s" , __func__ , req -> uri ) ) ;
 if ( req -> uri == NULL ) {
 event_debug ( ( "%s: bad request" , __func__ ) ) ;
 if ( req -> evcon -> state == EVCON_DISCONNECTED ) {
 evhttp_connection_fail ( req -> evcon , EVCON_HTTP_EOF ) ;
 }
 else {
 event_debug ( ( "%s: sending error" , __func__ ) ) ;
 evhttp_send_error ( req , HTTP_BADREQUEST , "Bad Request" ) ;
 }
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