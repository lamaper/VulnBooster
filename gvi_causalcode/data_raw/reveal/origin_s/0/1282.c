static void init_me_luts_bd ( int * bit16lut , int * bit4lut , int range , vpx_bit_depth_t bit_depth ) {
 int i ;
 for ( i = 0 ;
 i < range ;
 i ++ ) {
 const double q = vp9_convert_qindex_to_q ( i , bit_depth ) ;
 bit16lut [ i ] = ( int ) ( 0.0418 * q + 2.4107 ) ;
 bit4lut [ i ] = ( int ) ( 0.063 * q + 2.742 ) ;
 }
 }