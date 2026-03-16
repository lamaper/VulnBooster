static void evhttp_read_trailer ( struct evhttp_connection * evcon , struct evhttp_request * req ) {
 struct evbuffer * buf = evcon -> input_buffer ;
 switch ( evhttp_parse_headers ( req , buf ) ) {
 case DATA_CORRUPTED : evhttp_connection_fail ( evcon , EVCON_HTTP_INVALID_HEADER ) ;
 break ;
 case ALL_DATA_READ : event_del ( & evcon -> ev ) ;
 evhttp_connection_done ( evcon ) ;
 break ;
 case MORE_DATA_EXPECTED : default : evhttp_add_event ( & evcon -> ev , evcon -> timeout , HTTP_READ_TIMEOUT ) ;
 break ;
 }
 }