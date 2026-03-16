static void evhttp_read_firstline ( struct evhttp_connection * evcon , struct evhttp_request * req ) {
 enum message_read_status res ;
 res = evhttp_parse_firstline ( req , evcon -> input_buffer ) ;
 if ( res == DATA_CORRUPTED ) {
 event_debug ( ( "%s: bad header lines on %d\n" , __func__ , evcon -> fd ) ) ;
 evhttp_connection_fail ( evcon , EVCON_HTTP_INVALID_HEADER ) ;
 return ;
 }
 else if ( res == MORE_DATA_EXPECTED ) {
 evhttp_add_event ( & evcon -> ev , evcon -> timeout , HTTP_READ_TIMEOUT ) ;
 return ;
 }
 evcon -> state = EVCON_READING_HEADERS ;
 evhttp_read_header ( evcon , req ) ;
 }