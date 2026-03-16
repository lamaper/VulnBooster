static void decode_bgr_bitstream ( HYuvContext * s , int count ) {
 if ( s -> decorrelate ) {
 if ( s -> bitstream_bpp == 24 ) decode_bgr_1 ( s , count , 1 , 0 ) ;
 else decode_bgr_1 ( s , count , 1 , 1 ) ;
 }
 else {
 if ( s -> bitstream_bpp == 24 ) decode_bgr_1 ( s , count , 0 , 0 ) ;
 else decode_bgr_1 ( s , count , 0 , 1 ) ;
 }
 }