static void read_status ( struct recvbuf * rbufp , int restrict_mask ) {
 struct peer * peer ;
 const u_char * cp ;
 size_t n ;
 u_short a_st [ CTL_MAX_DATA_LEN / sizeof ( u_short ) ] ;


 peer = findpeerbyassoc ( res_associd ) ;
 if ( NULL == peer ) {
 ctl_error ( CERR_BADASSOC ) ;
 return ;
 }
 rpkt . status = htons ( ctlpeerstatus ( peer ) ) ;
 if ( res_authokay ) peer -> num_events = 0 ;
 for ( cp = def_peer_var ;
 * cp != 0 ;
 cp ++ ) ctl_putpeer ( ( int ) * cp , peer ) ;
 ctl_flushpkt ( 0 ) ;
 return ;
 }
 n = 0 ;
 rpkt . status = htons ( ctlsysstatus ( ) ) ;
 for ( peer = peer_list ;
 peer != NULL ;
 peer = peer -> p_link ) {
 a_st [ n ++ ] = htons ( peer -> associd ) ;
 a_st [ n ++ ] = htons ( ctlpeerstatus ( peer ) ) ;
 if ( n + 1 >= COUNTOF ( a_st ) ) {
 ctl_putdata ( ( void * ) a_st , n * sizeof ( a_st [ 0 ] ) , 1 ) ;
 n = 0 ;
 }
 }
 if ( n ) ctl_putdata ( ( void * ) a_st , n * sizeof ( a_st [ 0 ] ) , 1 ) ;
 ctl_flushpkt ( 0 ) ;
 }