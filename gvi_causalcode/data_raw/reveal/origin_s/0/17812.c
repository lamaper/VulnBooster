void init_control ( void ) {
 size_t i ;


 ctl_auth_keyid = 0 ;
 ctl_sys_last_event = EVNT_UNSPEC ;
 ctl_sys_num_events = 0 ;
 num_ctl_traps = 0 ;
 for ( i = 0 ;
 i < COUNTOF ( ctl_traps ) ;
 i ++ ) ctl_traps [ i ] . tr_flags = 0 ;
 }