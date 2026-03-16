static void control_unspec ( struct recvbuf * rbufp , int restrict_mask ) {
 struct peer * peer ;
 if ( res_associd ) {
 peer = findpeerbyassoc ( res_associd ) ;
 if ( NULL == peer ) {
 ctl_error ( CERR_BADASSOC ) ;
 return ;
 }
 rpkt . status = htons ( ctlpeerstatus ( peer ) ) ;
 }
 else rpkt . status = htons ( ctlsysstatus ( ) ) ;
 ctl_flushpkt ( 0 ) ;
 }