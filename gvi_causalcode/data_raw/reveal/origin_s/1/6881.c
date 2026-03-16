int main ( int argc , char * * argv ) {
 struct event signal_int ;
 event_init ( ) ;
 event_set ( & signal_int , SIGINT , EV_SIGNAL | EV_PERSIST , signal_cb , & signal_int ) ;
 event_add ( & signal_int , NULL ) ;
 event_dispatch ( ) ;
 return ( 0 ) ;
 }