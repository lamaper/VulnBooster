void vp8_encode_inter16x16 ( MACROBLOCK * x ) {
 vp8_build_inter_predictors_mb ( & x -> e_mbd ) ;
 vp8_subtract_mb ( x ) ;
 transform_mb ( x ) ;
 vp8_quantize_mb ( x ) ;
 if ( x -> optimize ) optimize_mb ( x ) ;
 }