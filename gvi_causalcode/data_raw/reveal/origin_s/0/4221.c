static void save_context ( VP9_COMP * cpi , int mi_row , int mi_col , ENTROPY_CONTEXT a [ 16 * MAX_MB_PLANE ] , ENTROPY_CONTEXT l [ 16 * MAX_MB_PLANE ] , PARTITION_CONTEXT sa [ 8 ] , PARTITION_CONTEXT sl [ 8 ] , BLOCK_SIZE bsize ) {
 const MACROBLOCK * const x = & cpi -> mb ;
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 int p ;
 const int num_4x4_blocks_wide = num_4x4_blocks_wide_lookup [ bsize ] ;
 const int num_4x4_blocks_high = num_4x4_blocks_high_lookup [ bsize ] ;
 int mi_width = num_8x8_blocks_wide_lookup [ bsize ] ;
 int mi_height = num_8x8_blocks_high_lookup [ bsize ] ;
 for ( p = 0 ;
 p < MAX_MB_PLANE ;
 ++ p ) {
 vpx_memcpy ( a + num_4x4_blocks_wide * p , xd -> above_context [ p ] + ( mi_col * 2 >> xd -> plane [ p ] . subsampling_x ) , ( sizeof ( ENTROPY_CONTEXT ) * num_4x4_blocks_wide ) >> xd -> plane [ p ] . subsampling_x ) ;
 vpx_memcpy ( l + num_4x4_blocks_high * p , xd -> left_context [ p ] + ( ( mi_row & MI_MASK ) * 2 >> xd -> plane [ p ] . subsampling_y ) , ( sizeof ( ENTROPY_CONTEXT ) * num_4x4_blocks_high ) >> xd -> plane [ p ] . subsampling_y ) ;
 }
 vpx_memcpy ( sa , xd -> above_seg_context + mi_col , sizeof ( * xd -> above_seg_context ) * mi_width ) ;
 vpx_memcpy ( sl , xd -> left_seg_context + ( mi_row & MI_MASK ) , sizeof ( xd -> left_seg_context [ 0 ] ) * mi_height ) ;
 }