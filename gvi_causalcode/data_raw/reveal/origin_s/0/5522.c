static int get_minq_index ( double maxq , double x3 , double x2 , double x1 , vpx_bit_depth_t bit_depth ) {
 int i ;
 const double minqtarget = MIN ( ( ( x3 * maxq + x2 ) * maxq + x1 ) * maxq , maxq ) ;
 if ( minqtarget <= 2.0 ) return 0 ;
 for ( i = 0 ;
 i < QINDEX_RANGE ;
 i ++ ) {
 if ( minqtarget <= vp9_convert_qindex_to_q ( i , bit_depth ) ) return i ;
 }
 return QINDEX_RANGE - 1 ;
 }