static void evhttp_read_header ( struct evhttp_connection * evcon , struct evhttp_request * req ) {
 enum message_read_status res ;
 int fd = evcon -> fd ;
 res = evhttp_parse_headers ( req , evcon -> input_buffer ) ;
 if ( res == DATA_CORRUPTED ) {
 event_debug ( ( "%s: bad header lines on %d\n" , __func__ , fd ) ) ;
 evhttp_connection_fail ( evcon , EVCON_HTTP_INVALID_HEADER ) ;
 return ;
 }
 else if ( res == MORE_DATA_EXPECTED ) {
 evhttp_add_event ( & evcon -> ev , evcon -> timeout , HTTP_READ_TIMEOUT ) ;
 return ;
 }
 switch ( req -> kind ) {
 case EVHTTP_REQUEST : event_debug ( ( "%s: checking for post data on %d\n" , __func__ , fd ) ) ;
 evhttp_get_body ( evcon , req ) ;
 break ;
 case EVHTTP_RESPONSE : if ( req -> response_code == HTTP_NOCONTENT || req -> response_code == HTTP_NOTMODIFIED || ( req -> response_code >= 100 && req -> response_code < 200 ) ) {
 event_debug ( ( "%s: skipping body for code %d\n" , __func__ , req -> response_code ) ) ;
 evhttp_connection_done ( evcon ) ;
 }
 else {
 event_debug ( ( "%s: start of read body for %s on %d\n" , __func__ , req -> remote_host , fd ) ) ;
 evhttp_get_body ( evcon , req ) ;
 }
 break ;
 default : event_warnx ( "%s: bad header on %d" , __func__ , fd ) ;
 evhttp_connection_fail ( evcon , EVCON_HTTP_INVALID_HEADER ) ;
 break ;
 }
 }