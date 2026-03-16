int main ( int argc , char * * argv ) {
 struct event signal_int ;
 struct event_base * base = event_base_new ( ) ;
 event_set ( & signal_int , SIGINT , EV_SIGNAL | EV_PERSIST , signal_cb , & signal_int ) ;
 event_base_set ( base , & signal_int ) ;
 event_add ( & signal_int , NULL ) ;
 event_base_dispatch ( base ) ;
 event_base_free ( base ) ;
 return ( 0 ) ;
 }