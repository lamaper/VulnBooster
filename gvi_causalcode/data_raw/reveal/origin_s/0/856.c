static void evport_dealloc ( struct event_base * base , void * arg ) {
 struct evport_data * evpd = arg ;
 evsignal_dealloc ( base ) ;
 close ( evpd -> ed_port ) ;
 if ( evpd -> ed_fds ) free ( evpd -> ed_fds ) ;
 free ( evpd ) ;
 }