void vp9_vaq_init ( ) {
 int i ;
 double base_ratio ;
 assert ( ENERGY_SPAN <= MAX_SEGMENTS ) ;
 vp9_clear_system_state ( ) ;
 base_ratio = 1.5 ;
 for ( i = ENERGY_MIN ;
 i <= ENERGY_MAX ;
 i ++ ) {
 Q_RATIO ( i ) = pow ( base_ratio , i / 3.0 ) ;
 }
 }