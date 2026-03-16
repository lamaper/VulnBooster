static int gfboost_qadjust ( int qindex , vpx_bit_depth_t bit_depth ) {
 const double q = vp9_convert_qindex_to_q ( qindex , bit_depth ) ;
 return ( int ) ( ( 0.00000828 * q * q * q ) + ( - 0.0055 * q * q ) + ( 1.32 * q ) + 79.3 ) ;
 }