void vp9_init_me_luts ( ) {
 int i ;
 for ( i = 0 ;
 i < QINDEX_RANGE ;
 ++ i ) {
 const double q = vp9_convert_qindex_to_q ( i ) ;
 sad_per_bit16lut [ i ] = ( int ) ( 0.0418 * q + 2.4107 ) ;
 sad_per_bit4lut [ i ] = ( int ) ( 0.063 * q + 2.742 ) ;
 }
 }