static void build_dcblock ( MACROBLOCK * x ) {
 short * src_diff_ptr = & x -> src_diff [ 384 ] ;
 int i ;
 for ( i = 0 ;
 i < 16 ;
 i ++ ) {
 src_diff_ptr [ i ] = x -> coeff [ i * 16 ] ;
 }
 }