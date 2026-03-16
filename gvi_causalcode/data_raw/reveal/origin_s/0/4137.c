void vp8_optimize_mbuv ( MACROBLOCK * x ) {
 int b ;
 ENTROPY_CONTEXT_PLANES t_above , t_left ;
 ENTROPY_CONTEXT * ta ;
 ENTROPY_CONTEXT * tl ;
 if ( ! x -> e_mbd . above_context ) return ;
 if ( ! x -> e_mbd . left_context ) return ;
 vpx_memcpy ( & t_above , x -> e_mbd . above_context , sizeof ( ENTROPY_CONTEXT_PLANES ) ) ;
 vpx_memcpy ( & t_left , x -> e_mbd . left_context , sizeof ( ENTROPY_CONTEXT_PLANES ) ) ;
 ta = ( ENTROPY_CONTEXT * ) & t_above ;
 tl = ( ENTROPY_CONTEXT * ) & t_left ;
 for ( b = 16 ;
 b < 24 ;
 b ++ ) {
 optimize_b ( x , b , PLANE_TYPE_UV , ta + vp8_block2above [ b ] , tl + vp8_block2left [ b ] ) ;
 }
 }