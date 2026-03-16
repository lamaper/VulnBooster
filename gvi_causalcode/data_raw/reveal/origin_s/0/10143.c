static void http_readcb ( struct bufferevent * bev , void * arg ) {
 const char * what = "This is funny" ;
 event_debug ( ( "%s: %s\n" , __func__ , EVBUFFER_DATA ( bev -> input ) ) ) ;
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
 bufferevent_disable ( bev , EV_READ ) ;
 if ( base ) event_base_loopexit ( base , NULL ) ;
 else event_loopexit ( NULL ) ;
 }
 }