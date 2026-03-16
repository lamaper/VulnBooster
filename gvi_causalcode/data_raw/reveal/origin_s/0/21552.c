static void * evport_init ( struct event_base * base ) {
 struct evport_data * evpd ;
 int i ;
 if ( evutil_getenv ( "EVENT_NOEVPORT" ) ) return ( NULL ) ;
 if ( ! ( evpd = calloc ( 1 , sizeof ( struct evport_data ) ) ) ) return ( NULL ) ;
 if ( ( evpd -> ed_port = port_create ( ) ) == - 1 ) {
 free ( evpd ) ;
 return ( NULL ) ;
 }
 evpd -> ed_fds = calloc ( DEFAULT_NFDS , sizeof ( struct fd_info ) ) ;
 if ( evpd -> ed_fds == NULL ) {
 close ( evpd -> ed_port ) ;
 free ( evpd ) ;
 return ( NULL ) ;
 }
 evpd -> ed_nevents = DEFAULT_NFDS ;
 for ( i = 0 ;
 i < EVENTS_PER_GETN ;
 i ++ ) evpd -> ed_pending [ i ] = - 1 ;
 evsignal_init ( base ) ;
 return ( evpd ) ;
 }