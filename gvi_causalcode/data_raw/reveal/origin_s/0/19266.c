static void evhttp_connection_stop_detectclose ( struct evhttp_connection * evcon ) {
 evcon -> flags &= ~ EVHTTP_CON_CLOSEDETECT ;
 event_del ( & evcon -> close_ev ) ;
 }