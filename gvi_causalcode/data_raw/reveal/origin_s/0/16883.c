static void estimate_block_intra ( int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , void * arg ) {
 struct estimate_block_intra_args * const args = arg ;
 VP9_COMP * const cpi = args -> cpi ;
 MACROBLOCK * const x = args -> x ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 struct macroblock_plane * const p = & x -> plane [ 0 ] ;
 struct macroblockd_plane * const pd = & xd -> plane [ 0 ] ;
 const BLOCK_SIZE bsize_tx = txsize_to_bsize [ tx_size ] ;
 uint8_t * const src_buf_base = p -> src . buf ;
 uint8_t * const dst_buf_base = pd -> dst . buf ;
 const int src_stride = p -> src . stride ;
 const int dst_stride = pd -> dst . stride ;
 int i , j ;
 int rate ;
 int64_t dist ;
 unsigned int var_y , sse_y ;
 txfrm_block_to_raster_xy ( plane_bsize , tx_size , block , & i , & j ) ;
 assert ( plane == 0 ) ;
 ( void ) plane ;
 p -> src . buf = & src_buf_base [ 4 * ( j * src_stride + i ) ] ;
 pd -> dst . buf = & dst_buf_base [ 4 * ( j * dst_stride + i ) ] ;
 vp9_predict_intra_block ( xd , block >> ( 2 * tx_size ) , b_width_log2 ( plane_bsize ) , tx_size , args -> mode , p -> src . buf , src_stride , pd -> dst . buf , dst_stride , i , j , 0 ) ;
 model_rd_for_sb_y ( cpi , bsize_tx , x , xd , & rate , & dist , & var_y , & sse_y ) ;
 p -> src . buf = src_buf_base ;
 pd -> dst . buf = dst_buf_base ;
 args -> rate += rate ;
 args -> dist += dist ;
 }