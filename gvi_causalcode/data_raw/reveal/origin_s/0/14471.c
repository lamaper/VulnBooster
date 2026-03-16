static void http_badreq_readcb ( struct bufferevent * bev , void * arg ) {
 const char * what = "Hello, 127.0.0.1" ;
 const char * bad_request = "400 Bad Request" ;
 event_debug ( ( "%s: %s\n" , __func__ , EVBUFFER_DATA ( bev -> input ) ) ) ;
 if ( evbuffer_find ( bev -> input , ( const unsigned char * ) bad_request , strlen ( bad_request ) ) != NULL ) {
 event_debug ( ( "%s: bad request detected" , __func__ ) ) ;
 test_ok = - 10 ;
 bufferevent_disable ( bev , EV_READ ) ;
 event_loopexit ( NULL ) ;
 return ;
 }
 if ( evbuffer_find ( bev -> input , ( const unsigned char * ) what , strlen ( what ) ) != NULL ) {
 struct evhttp_request * req = evhttp_request_new ( NULL , NULL ) ;
 enum message_read_status done ;
 req -> kind = EVHTTP_RESPONSE ;
 done = evhttp_parse_firstline ( req , bev -> input ) ;
 if ( done != ALL_DATA_READ ) goto out ;
 done = evhttp_parse_headers ( req , bev -> input ) ;
 if ( done != ALL_DATA_READ ) goto out ;
 if ( done == 1 && evhttp_find_header ( req -> input_headers , "Content-Type" ) != NULL ) test_ok ++ ;
 out : evhttp_request_free ( req ) ;
 evbuffer_drain ( bev -> input , EVBUFFER_LENGTH ( bev -> input ) ) ;
 }
 shutdown ( bev -> ev_read . ev_fd , SHUT_WR ) ;
 }