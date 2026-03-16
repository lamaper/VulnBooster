void vp8_encode_inter16x16y ( MACROBLOCK * x ) {
 BLOCK * b = & x -> block [ 0 ] ;
 vp8_build_inter16x16_predictors_mby ( & x -> e_mbd , x -> e_mbd . dst . y_buffer , x -> e_mbd . dst . y_stride ) ;
 vp8_subtract_mby ( x -> src_diff , * ( b -> base_src ) , b -> src_stride , x -> e_mbd . dst . y_buffer , x -> e_mbd . dst . y_stride ) ;
 transform_mby ( x ) ;
 vp8_quantize_mby ( x ) ;
 vp8_inverse_transform_mby ( & x -> e_mbd ) ;
 }