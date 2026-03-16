int event_loop ( int flags ) {
 return event_base_loop ( current_base , flags ) ;
 }