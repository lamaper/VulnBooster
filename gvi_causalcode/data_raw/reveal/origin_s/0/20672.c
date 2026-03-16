static void sbr_qmf_pre_shuffle_c ( float * z ) {
 union av_intfloat32 * zi = ( union av_intfloat32 * ) z ;
 int k ;
 zi [ 64 ] . i = zi [ 0 ] . i ;
 zi [ 65 ] . i = zi [ 1 ] . i ;
 for ( k = 1 ;
 k < 31 ;
 k += 2 ) {
 zi [ 64 + 2 * k + 0 ] . i = zi [ 64 - k ] . i ^ ( 1U << 31 ) ;
 zi [ 64 + 2 * k + 1 ] . i = zi [ k + 1 ] . i ;
 zi [ 64 + 2 * k + 2 ] . i = zi [ 63 - k ] . i ^ ( 1U << 31 ) ;
 zi [ 64 + 2 * k + 3 ] . i = zi [ k + 2 ] . i ;
 }
 zi [ 64 + 2 * 31 + 0 ] . i = zi [ 64 - 31 ] . i ^ ( 1U << 31 ) ;
 zi [ 64 + 2 * 31 + 1 ] . i = zi [ 31 + 1 ] . i ;
 }