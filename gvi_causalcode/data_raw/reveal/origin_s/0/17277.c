static void arm_mptimer_reset ( DeviceState * dev ) {
 ARMMPTimerState * s = FROM_SYSBUS ( ARMMPTimerState , SYS_BUS_DEVICE ( dev ) ) ;
 int i ;
 for ( i = 0 ;
 i < ARRAY_SIZE ( s -> timerblock ) ;
 i ++ ) {
 timerblock_reset ( & s -> timerblock [ i ] ) ;
 }
 }