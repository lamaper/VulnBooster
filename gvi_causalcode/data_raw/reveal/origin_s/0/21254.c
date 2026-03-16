static int evport_del ( void * arg , struct event * ev ) {
 struct evport_data * evpd = arg ;
 struct fd_info * fdi ;
 int i ;
 int associated = 1 ;
 check_evportop ( evpd ) ;
 if ( ev -> ev_events & EV_SIGNAL ) {
 return ( evsignal_del ( ev ) ) ;
 }
 if ( evpd -> ed_nevents < ev -> ev_fd ) {
 return ( - 1 ) ;
 }
 for ( i = 0 ;
 i < EVENTS_PER_GETN ;
 ++ i ) {
 if ( evpd -> ed_pending [ i ] == ev -> ev_fd ) {
 associated = 0 ;
 break ;
 }
 }
 fdi = & evpd -> ed_fds [ ev -> ev_fd ] ;
 if ( ev -> ev_events & EV_READ ) fdi -> fdi_revt = NULL ;
 if ( ev -> ev_events & EV_WRITE ) fdi -> fdi_wevt = NULL ;
 if ( associated ) {
 if ( ! FDI_HAS_EVENTS ( fdi ) && port_dissociate ( evpd -> ed_port , PORT_SOURCE_FD , ev -> ev_fd ) == - 1 ) {
 if ( errno != EBADFD ) {
 event_warn ( "port_dissociate" ) ;
 return ( - 1 ) ;
 }
 }
 else {
 if ( FDI_HAS_EVENTS ( fdi ) ) {
 return ( reassociate ( evpd , fdi , ev -> ev_fd ) ) ;
 }
 }
 }
 else {
 if ( fdi -> fdi_revt == NULL && fdi -> fdi_wevt == NULL ) {
 evpd -> ed_pending [ i ] = - 1 ;
 }
 }
 return 0 ;
 }