u_short ctlsysstatus ( void ) {
 register u_char this_clock ;
 this_clock = CTL_SST_TS_UNSPEC ;

 if ( CTL_SST_TS_UNSPEC != sys_peer -> sstclktype ) this_clock = sys_peer -> sstclktype ;
 else if ( sys_peer -> refclktype < COUNTOF ( clocktypes ) ) this_clock = clocktypes [ sys_peer -> refclktype ] ;
 }


 }