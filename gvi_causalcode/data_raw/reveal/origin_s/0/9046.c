static void set_entropy_context_b ( int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , void * arg ) {
 struct tokenize_b_args * const args = arg ;
 MACROBLOCKD * const xd = args -> xd ;
 struct macroblock_plane * p = & args -> cpi -> mb . plane [ plane ] ;
 struct macroblockd_plane * pd = & xd -> plane [ plane ] ;
 int aoff , loff ;
 txfrm_block_to_raster_xy ( plane_bsize , tx_size , block , & aoff , & loff ) ;
 vp9_set_contexts ( xd , pd , plane_bsize , tx_size , p -> eobs [ block ] > 0 , aoff , loff ) ;
 }