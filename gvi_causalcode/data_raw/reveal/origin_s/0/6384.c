static void read_ifstats ( struct recvbuf * rbufp ) {
 u_int ifidx ;
 endpt * la ;
 for ( ifidx = 0 ;
 ifidx < sys_ifnum ;
 ifidx ++ ) {
 for ( la = ep_list ;
 la != NULL ;
 la = la -> elink ) if ( ifidx == la -> ifnum ) break ;
 if ( NULL == la ) continue ;
 send_ifstats_entry ( la , ifidx ) ;
 }
 ctl_flushpkt ( 0 ) ;
 }