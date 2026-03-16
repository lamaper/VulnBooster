static void reconstruct_inter_block ( int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , void * arg ) {
 struct inter_args * args = ( struct inter_args * ) arg ;
 VP9_COMMON * const cm = args -> cm ;
 MACROBLOCKD * const xd = args -> xd ;
 struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 int x , y , eob ;
 txfrm_block_to_raster_xy ( plane_bsize , tx_size , block , & x , & y ) ;
 eob = vp9_decode_block_tokens ( cm , xd , plane , block , plane_bsize , x , y , tx_size , args -> r ) ;
 inverse_transform_block ( xd , plane , block , tx_size , & pd -> dst . buf [ 4 * y * pd -> dst . stride + 4 * x ] , pd -> dst . stride , eob ) ;
 * args -> eobtotal += eob ;
 }