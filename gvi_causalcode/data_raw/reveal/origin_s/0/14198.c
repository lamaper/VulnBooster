static void vp8_subtract_mb ( MACROBLOCK * x ) {
 BLOCK * b = & x -> block [ 0 ] ;
 vp8_subtract_mby ( x -> src_diff , * ( b -> base_src ) , b -> src_stride , x -> e_mbd . dst . y_buffer , x -> e_mbd . dst . y_stride ) ;
 vp8_subtract_mbuv ( x -> src_diff , x -> src . u_buffer , x -> src . v_buffer , x -> src . uv_stride , x -> e_mbd . dst . u_buffer , x -> e_mbd . dst . v_buffer , x -> e_mbd . dst . uv_stride ) ;
 }