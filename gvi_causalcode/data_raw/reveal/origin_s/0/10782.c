static void sbr_qmf_deint_neg_c ( float * v , const float * src ) {
 const union av_intfloat32 * si = ( const union av_intfloat32 * ) src ;
 union av_intfloat32 * vi = ( union av_intfloat32 * ) v ;
 int i ;
 for ( i = 0 ;
 i < 32 ;
 i ++ ) {
 vi [ i ] . i = si [ 63 - 2 * i ] . i ;
 vi [ 63 - i ] . i = si [ 63 - 2 * i - 1 ] . i ^ ( 1U << 31 ) ;
 }
 }