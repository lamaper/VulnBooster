static void set_trap ( struct recvbuf * rbufp , int restrict_mask ) {
 int traptype ;
 if ( restrict_mask & RES_NOTRAP ) {
 ctl_error ( CERR_PERMISSION ) ;
 return ;
 }
 traptype = TRAP_TYPE_PRIO ;
 if ( restrict_mask & RES_LPTRAP ) traptype = TRAP_TYPE_NONPRIO ;
 if ( ! ctlsettrap ( & rbufp -> recv_srcadr , rbufp -> dstadr , traptype , ( int ) res_version ) ) ctl_error ( CERR_NORESOURCE ) ;
 ctl_flushpkt ( 0 ) ;
 }