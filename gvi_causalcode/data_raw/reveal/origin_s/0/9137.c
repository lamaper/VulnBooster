void ff_MPV_decode_mb ( MpegEncContext * s , int16_t block [ 12 ] [ 64 ] ) {

 MPV_decode_mb_internal ( s , block , 1 ) ;
 }
 else # endif MPV_decode_mb_internal ( s , block , 0 ) ;
 }