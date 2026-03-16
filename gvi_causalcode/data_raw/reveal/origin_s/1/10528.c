static void sbr_qmf_deint_bfly_c ( float * v , const float * src0 , const float * src1 ) {
 int i ;
 for ( i = 0 ;
 i < 64 ;
 i ++ ) {
 v [ i ] = src0 [ i ] - src1 [ 63 - i ] ;
 v [ 127 - i ] = src0 [ i ] + src1 [ 63 - i ] ;
 }
 }