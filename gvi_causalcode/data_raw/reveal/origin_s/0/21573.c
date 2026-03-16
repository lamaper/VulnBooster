static void sbr_qmf_post_shuffle_c ( float W [ 32 ] [ 2 ] , const float * z ) {
 const union av_intfloat32 * zi = ( const union av_intfloat32 * ) z ;
 union av_intfloat32 * Wi = ( union av_intfloat32 * ) W ;
 int k ;
 for ( k = 0 ;
 k < 32 ;
 k += 2 ) {
 Wi [ 2 * k + 0 ] . i = zi [ 63 - k ] . i ^ ( 1U << 31 ) ;
 Wi [ 2 * k + 1 ] . i = zi [ k + 0 ] . i ;
 Wi [ 2 * k + 2 ] . i = zi [ 62 - k ] . i ^ ( 1U << 31 ) ;
 Wi [ 2 * k + 3 ] . i = zi [ k + 1 ] . i ;
 }
 }