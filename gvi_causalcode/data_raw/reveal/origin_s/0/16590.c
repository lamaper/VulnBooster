static void optimize_mb ( MACROBLOCK * x ) {
 int b ;
 int type ;
 int has_2nd_order ;
 ENTROPY_CONTEXT_PLANES t_above , t_left ;
 ENTROPY_CONTEXT * ta ;
 ENTROPY_CONTEXT * tl ;
 vpx_memcpy ( & t_above , x -> e_mbd . above_context , sizeof ( ENTROPY_CONTEXT_PLANES ) ) ;
 vpx_memcpy ( & t_left , x -> e_mbd . left_context , sizeof ( ENTROPY_CONTEXT_PLANES ) ) ;
 ta = ( ENTROPY_CONTEXT * ) & t_above ;
 tl = ( ENTROPY_CONTEXT * ) & t_left ;
 has_2nd_order = ( x -> e_mbd . mode_info_context -> mbmi . mode != B_PRED && x -> e_mbd . mode_info_context -> mbmi . mode != SPLITMV ) ;
 type = has_2nd_order ? PLANE_TYPE_Y_NO_DC : PLANE_TYPE_Y_WITH_DC ;
 for ( b = 0 ;
 b < 16 ;
 b ++ ) {
 optimize_b ( x , b , type , ta + vp8_block2above [ b ] , tl + vp8_block2left [ b ] ) ;
 }
 for ( b = 16 ;
 b < 24 ;
 b ++ ) {
 optimize_b ( x , b , PLANE_TYPE_UV , ta + vp8_block2above [ b ] , tl + vp8_block2left [ b ] ) ;
 }
 if ( has_2nd_order ) {
 b = 24 ;
 optimize_b ( x , b , PLANE_TYPE_Y2 , ta + vp8_block2above [ b ] , tl + vp8_block2left [ b ] ) ;
 check_reset_2nd_coeffs ( & x -> e_mbd , PLANE_TYPE_Y2 , ta + vp8_block2above [ b ] , tl + vp8_block2left [ b ] ) ;
 }
 }