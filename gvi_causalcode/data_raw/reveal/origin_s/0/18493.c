static void unset_trap ( struct recvbuf * rbufp , int restrict_mask ) {
 int traptype ;
 traptype = TRAP_TYPE_PRIO ;
 if ( restrict_mask & RES_LPTRAP ) traptype = TRAP_TYPE_NONPRIO ;
 if ( ! ctlclrtrap ( & rbufp -> recv_srcadr , rbufp -> dstadr , traptype ) ) ctl_error ( CERR_BADASSOC ) ;
 ctl_flushpkt ( 0 ) ;
 }