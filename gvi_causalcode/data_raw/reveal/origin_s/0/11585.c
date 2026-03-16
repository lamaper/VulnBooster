static void writecb ( struct bufferevent * bev , void * arg ) {
 if ( EVBUFFER_LENGTH ( bev -> output ) == 0 ) test_ok ++ ;
 }