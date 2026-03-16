static void e1000e_intmgr_timer_pause ( E1000IntrDelayTimer * timer ) {
 if ( timer -> running ) {
 timer_del ( timer -> timer ) ;
 }
 }