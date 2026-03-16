static void vapic_reset ( DeviceState * dev ) {
 VAPICROMState * s = DO_UPCAST ( VAPICROMState , busdev . qdev , dev ) ;
 if ( s -> state == VAPIC_ACTIVE ) {
 s -> state = VAPIC_STANDBY ;
 }
 vapic_enable_tpr_reporting ( false ) ;
 }