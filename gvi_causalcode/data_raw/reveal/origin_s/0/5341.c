static void http_complete_write ( int fd , short what , void * arg ) {
 struct bufferevent * bev = arg ;
 const char * http_request = "host\r\n" "Connection: close\r\n" "\r\n" ;
 bufferevent_write ( bev , http_request , strlen ( http_request ) ) ;
 }