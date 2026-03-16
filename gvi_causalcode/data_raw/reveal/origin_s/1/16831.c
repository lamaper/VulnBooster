static int gfboost_qadjust ( int qindex ) {
 const double q = vp9_convert_qindex_to_q ( qindex ) ;
 return ( int ) ( ( 0.00000828 * q * q * q ) + ( - 0.0055 * q * q ) + ( 1.32 * q ) + 79.3 ) ;
 }