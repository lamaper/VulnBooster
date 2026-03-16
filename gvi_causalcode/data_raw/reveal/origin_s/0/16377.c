void vp9_subtract_plane ( MACROBLOCK * x , BLOCK_SIZE bsize , int plane ) {
 struct macroblock_plane * const p = & x -> plane [ plane ] ;
 const struct macroblockd_plane * const pd = & x -> e_mbd . plane [ plane ] ;
 const BLOCK_SIZE plane_bsize = get_plane_block_size ( bsize , pd ) ;
 const int bw = 4 * num_4x4_blocks_wide_lookup [ plane_bsize ] ;
 const int bh = 4 * num_4x4_blocks_high_lookup [ plane_bsize ] ;
 vp9_subtract_block ( bh , bw , p -> src_diff , bw , p -> src . buf , p -> src . stride , pd -> dst . buf , pd -> dst . stride ) ;
 }