static void evhttp_detect_close_cb ( int fd , short what , void * arg ) {
 struct evhttp_connection * evcon = arg ;
 evhttp_connection_reset ( evcon ) ;
 }