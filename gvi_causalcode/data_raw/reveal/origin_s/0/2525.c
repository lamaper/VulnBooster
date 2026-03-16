static void model_rd_for_sb_y ( VP9_COMP * cpi , BLOCK_SIZE bsize , MACROBLOCK * x , MACROBLOCKD * xd , int * out_rate_sum , int64_t * out_dist_sum , unsigned int * var_y , unsigned int * sse_y ) {
 unsigned int sse ;
 int rate ;
 int64_t dist ;
 struct macroblock_plane * const p = & x -> plane [ 0 ] ;
 struct macroblockd_plane * const pd = & xd -> plane [ 0 ] ;
 const uint32_t dc_quant = pd -> dequant [ 0 ] ;
 const uint32_t ac_quant = pd -> dequant [ 1 ] ;
 unsigned int var = cpi -> fn_ptr [ bsize ] . vf ( p -> src . buf , p -> src . stride , pd -> dst . buf , pd -> dst . stride , & sse ) ;
 * var_y = var ;
 * sse_y = sse ;
 if ( sse < dc_quant * dc_quant >> 6 ) x -> skip_txfm [ 0 ] = 1 ;
 else if ( var < ac_quant * ac_quant >> 6 ) x -> skip_txfm [ 0 ] = 2 ;
 else x -> skip_txfm [ 0 ] = 0 ;
 if ( cpi -> common . tx_mode == TX_MODE_SELECT ) {
 if ( sse > ( var << 2 ) ) xd -> mi [ 0 ] . src_mi -> mbmi . tx_size = MIN ( max_txsize_lookup [ bsize ] , tx_mode_to_biggest_tx_size [ cpi -> common . tx_mode ] ) ;
 else xd -> mi [ 0 ] . src_mi -> mbmi . tx_size = TX_8X8 ;
 }
 else {
 xd -> mi [ 0 ] . src_mi -> mbmi . tx_size = MIN ( max_txsize_lookup [ bsize ] , tx_mode_to_biggest_tx_size [ cpi -> common . tx_mode ] ) ;
 }
 vp9_model_rd_from_var_lapndz ( sse - var , 1 << num_pels_log2_lookup [ bsize ] , dc_quant >> 3 , & rate , & dist ) ;
 * out_rate_sum = rate >> 1 ;
 * out_dist_sum = dist << 3 ;
 vp9_model_rd_from_var_lapndz ( var , 1 << num_pels_log2_lookup [ bsize ] , ac_quant >> 3 , & rate , & dist ) ;
 * out_rate_sum += rate ;
 * out_dist_sum += dist << 4 ;
 }