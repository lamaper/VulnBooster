static void evhttp_read_body ( struct evhttp_connection * evcon , struct evhttp_request * req ) {
 struct evbuffer * buf = evcon -> input_buffer ;
 if ( req -> chunked ) {
 switch ( evhttp_handle_chunked_read ( req , buf ) ) {
 case ALL_DATA_READ : evcon -> state = EVCON_READING_TRAILER ;
 evhttp_read_trailer ( evcon , req ) ;
 return ;
 case DATA_CORRUPTED : evhttp_connection_fail ( evcon , EVCON_HTTP_INVALID_HEADER ) ;
 return ;
 case REQUEST_CANCELED : evhttp_request_free ( req ) ;
 return ;
 case MORE_DATA_EXPECTED : default : break ;
 }
 }
 else if ( req -> ntoread < 0 ) {
 evbuffer_add_buffer ( req -> input_buffer , buf ) ;
 }
 else if ( EVBUFFER_LENGTH ( buf ) >= req -> ntoread ) {
 evbuffer_add ( req -> input_buffer , EVBUFFER_DATA ( buf ) , ( size_t ) req -> ntoread ) ;
 evbuffer_drain ( buf , ( size_t ) req -> ntoread ) ;
 req -> ntoread = 0 ;
 evhttp_connection_done ( evcon ) ;
 return ;
 }
 event_set ( & evcon -> ev , evcon -> fd , EV_READ , evhttp_read , evcon ) ;
 EVHTTP_BASE_SET ( evcon , & evcon -> ev ) ;
 evhttp_add_event ( & evcon -> ev , evcon -> timeout , HTTP_READ_TIMEOUT ) ;
 }