static int evhttp_connected ( struct evhttp_connection * evcon ) {
 switch ( evcon -> state ) {
 case EVCON_DISCONNECTED : case EVCON_CONNECTING : return ( 0 ) ;
 case EVCON_IDLE : case EVCON_READING_FIRSTLINE : case EVCON_READING_HEADERS : case EVCON_READING_BODY : case EVCON_READING_TRAILER : case EVCON_WRITING : default : return ( 1 ) ;
 }
 }