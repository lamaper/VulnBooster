static int find_fp_qindex ( vpx_bit_depth_t bit_depth ) {
 int i ;
 for ( i = 0 ;
 i < QINDEX_RANGE ;
 ++ i ) if ( vp9_convert_qindex_to_q ( i , bit_depth ) >= FIRST_PASS_Q ) break ;
 if ( i == QINDEX_RANGE ) i -- ;
 return i ;
 }