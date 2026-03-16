static int evport_add ( void * arg , struct event * ev ) {
 struct evport_data * evpd = arg ;
 struct fd_info * fdi ;
 int factor ;
 check_evportop ( evpd ) ;
 if ( ev -> ev_events & EV_SIGNAL ) return ( evsignal_add ( ev ) ) ;
 factor = 1 ;
 while ( ev -> ev_fd >= factor * evpd -> ed_nevents ) factor *= 2 ;
 if ( factor > 1 ) {
 if ( - 1 == grow ( evpd , factor ) ) {
 return ( - 1 ) ;
 }
 }
 fdi = & evpd -> ed_fds [ ev -> ev_fd ] ;
 if ( ev -> ev_events & EV_READ ) fdi -> fdi_revt = ev ;
 if ( ev -> ev_events & EV_WRITE ) fdi -> fdi_wevt = ev ;
 return reassociate ( evpd , fdi , ev -> ev_fd ) ;
 }