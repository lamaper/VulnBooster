static void terminate_chunked_client ( int fd , short event , void * arg ) {
 struct terminate_state * state = arg ;
 bufferevent_free ( state -> bev ) ;
 EVUTIL_CLOSESOCKET ( state -> fd ) ;
 }