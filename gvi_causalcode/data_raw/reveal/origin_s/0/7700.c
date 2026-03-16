static void http_chunked_errorcb ( struct bufferevent * bev , short what , void * arg ) {
 if ( ! test_ok ) goto out ;
 test_ok = - 1 ;
 if ( ( what & EVBUFFER_EOF ) != 0 ) {
 struct evhttp_request * req = evhttp_request_new ( NULL , NULL ) ;
 const char * header ;
 enum message_read_status done ;
 req -> kind = EVHTTP_RESPONSE ;
 done = evhttp_parse_firstline ( req , EVBUFFER_INPUT ( bev ) ) ;
 if ( done != ALL_DATA_READ ) goto out ;
 done = evhttp_parse_headers ( req , EVBUFFER_INPUT ( bev ) ) ;
 if ( done != ALL_DATA_READ ) goto out ;
 header = evhttp_find_header ( req -> input_headers , "Transfer-Encoding" ) ;
 if ( header == NULL || strcmp ( header , "chunked" ) ) goto out ;
 header = evhttp_find_header ( req -> input_headers , "Connection" ) ;
 if ( header == NULL || strcmp ( header , "close" ) ) goto out ;
 header = evbuffer_readline ( EVBUFFER_INPUT ( bev ) ) ;
 if ( header == NULL ) goto out ;
 if ( strcmp ( header , "d" ) ) goto out ;
 free ( ( char * ) header ) ;
 if ( strncmp ( ( char * ) EVBUFFER_DATA ( EVBUFFER_INPUT ( bev ) ) , "This is funny" , 13 ) ) goto out ;
 evbuffer_drain ( EVBUFFER_INPUT ( bev ) , 13 + 2 ) ;
 header = evbuffer_readline ( EVBUFFER_INPUT ( bev ) ) ;
 if ( header == NULL ) goto out ;
 if ( strcmp ( header , "12" ) ) goto out ;
 free ( ( char * ) header ) ;
 if ( strncmp ( ( char * ) EVBUFFER_DATA ( EVBUFFER_INPUT ( bev ) ) , "but not hilarious." , 18 ) ) goto out ;
 evbuffer_drain ( EVBUFFER_INPUT ( bev ) , 18 + 2 ) ;
 header = evbuffer_readline ( EVBUFFER_INPUT ( bev ) ) ;
 if ( header == NULL ) goto out ;
 if ( strcmp ( header , "8" ) ) goto out ;
 free ( ( char * ) header ) ;
 if ( strncmp ( ( char * ) EVBUFFER_DATA ( EVBUFFER_INPUT ( bev ) ) , "bwv 1052." , 8 ) ) goto out ;
 evbuffer_drain ( EVBUFFER_INPUT ( bev ) , 8 + 2 ) ;
 header = evbuffer_readline ( EVBUFFER_INPUT ( bev ) ) ;
 if ( header == NULL ) goto out ;
 if ( strcmp ( header , "0" ) ) goto out ;
 free ( ( char * ) header ) ;
 test_ok = 2 ;
 }
 out : event_loopexit ( NULL ) ;
 }