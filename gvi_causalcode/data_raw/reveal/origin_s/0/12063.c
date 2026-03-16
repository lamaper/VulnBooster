static void terminate_readcb ( struct bufferevent * bev , void * arg ) {
 evbuffer_drain ( bev -> output , - 1 ) ;
 }