static int64_t rd_pick_intra4x4block ( VP9_COMP * cpi , MACROBLOCK * x , int ib , PREDICTION_MODE * best_mode , const int * bmode_costs , ENTROPY_CONTEXT * a , ENTROPY_CONTEXT * l , int * bestrate , int * bestratey , int64_t * bestdistortion , BLOCK_SIZE bsize , int64_t rd_thresh ) {
 PREDICTION_MODE mode ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 int64_t best_rd = rd_thresh ;
 struct macroblock_plane * p = & x -> plane [ 0 ] ;
 struct macroblockd_plane * pd = & xd -> plane [ 0 ] ;
 const int src_stride = p -> src . stride ;
 const int dst_stride = pd -> dst . stride ;
 const uint8_t * src_init = & p -> src . buf [ raster_block_offset ( BLOCK_8X8 , ib , src_stride ) ] ;
 uint8_t * dst_init = & pd -> dst . buf [ raster_block_offset ( BLOCK_8X8 , ib , dst_stride ) ] ;
 ENTROPY_CONTEXT ta [ 2 ] , tempa [ 2 ] ;
 ENTROPY_CONTEXT tl [ 2 ] , templ [ 2 ] ;
 const int num_4x4_blocks_wide = num_4x4_blocks_wide_lookup [ bsize ] ;
 const int num_4x4_blocks_high = num_4x4_blocks_high_lookup [ bsize ] ;
 int idx , idy ;
 uint8_t best_dst [ 8 * 8 ] ;
 assert ( ib < 4 ) ;
 vpx_memcpy ( ta , a , sizeof ( ta ) ) ;
 vpx_memcpy ( tl , l , sizeof ( tl ) ) ;
 xd -> mi [ 0 ] -> mbmi . tx_size = TX_4X4 ;
 for ( mode = DC_PRED ;
 mode <= TM_PRED ;
 ++ mode ) {
 int64_t this_rd ;
 int ratey = 0 ;
 int64_t distortion = 0 ;
 int rate = bmode_costs [ mode ] ;
 if ( ! ( cpi -> sf . intra_y_mode_mask [ TX_4X4 ] & ( 1 << mode ) ) ) continue ;
 if ( cpi -> sf . mode_search_skip_flags & FLAG_SKIP_INTRA_DIRMISMATCH ) {
 if ( conditional_skipintra ( mode , * best_mode ) ) continue ;
 }
 vpx_memcpy ( tempa , ta , sizeof ( ta ) ) ;
 vpx_memcpy ( templ , tl , sizeof ( tl ) ) ;
 for ( idy = 0 ;
 idy < num_4x4_blocks_high ;
 ++ idy ) {
 for ( idx = 0 ;
 idx < num_4x4_blocks_wide ;
 ++ idx ) {
 const int block = ib + idy * 2 + idx ;
 const uint8_t * const src = & src_init [ idx * 4 + idy * 4 * src_stride ] ;
 uint8_t * const dst = & dst_init [ idx * 4 + idy * 4 * dst_stride ] ;
 int16_t * const src_diff = raster_block_offset_int16 ( BLOCK_8X8 , block , p -> src_diff ) ;
 int16_t * const coeff = BLOCK_OFFSET ( x -> plane [ 0 ] . coeff , block ) ;
 xd -> mi [ 0 ] -> bmi [ block ] . as_mode = mode ;
 vp9_predict_intra_block ( xd , block , 1 , TX_4X4 , mode , x -> skip_encode ? src : dst , x -> skip_encode ? src_stride : dst_stride , dst , dst_stride , idx , idy , 0 ) ;
 vp9_subtract_block ( 4 , 4 , src_diff , 8 , src , src_stride , dst , dst_stride ) ;
 if ( xd -> lossless ) {
 const scan_order * so = & vp9_default_scan_orders [ TX_4X4 ] ;
 vp9_fwht4x4 ( src_diff , coeff , 8 ) ;
 vp9_regular_quantize_b_4x4 ( x , 0 , block , so -> scan , so -> iscan ) ;
 ratey += cost_coeffs ( x , 0 , block , tempa + idx , templ + idy , TX_4X4 , so -> scan , so -> neighbors , cpi -> sf . use_fast_coef_costing ) ;
 if ( RDCOST ( x -> rdmult , x -> rddiv , ratey , distortion ) >= best_rd ) goto next ;
 vp9_iwht4x4_add ( BLOCK_OFFSET ( pd -> dqcoeff , block ) , dst , dst_stride , p -> eobs [ block ] ) ;
 }
 else {
 int64_t unused ;
 const TX_TYPE tx_type = get_tx_type_4x4 ( PLANE_TYPE_Y , xd , block ) ;
 const scan_order * so = & vp9_scan_orders [ TX_4X4 ] [ tx_type ] ;
 vp9_fht4x4 ( src_diff , coeff , 8 , tx_type ) ;
 vp9_regular_quantize_b_4x4 ( x , 0 , block , so -> scan , so -> iscan ) ;
 ratey += cost_coeffs ( x , 0 , block , tempa + idx , templ + idy , TX_4X4 , so -> scan , so -> neighbors , cpi -> sf . use_fast_coef_costing ) ;
 distortion += vp9_block_error ( coeff , BLOCK_OFFSET ( pd -> dqcoeff , block ) , 16 , & unused ) >> 2 ;
 if ( RDCOST ( x -> rdmult , x -> rddiv , ratey , distortion ) >= best_rd ) goto next ;
 vp9_iht4x4_add ( tx_type , BLOCK_OFFSET ( pd -> dqcoeff , block ) , dst , dst_stride , p -> eobs [ block ] ) ;
 }
 }
 }
 rate += ratey ;
 this_rd = RDCOST ( x -> rdmult , x -> rddiv , rate , distortion ) ;
 if ( this_rd < best_rd ) {
 * bestrate = rate ;
 * bestratey = ratey ;
 * bestdistortion = distortion ;
 best_rd = this_rd ;
 * best_mode = mode ;
 vpx_memcpy ( a , tempa , sizeof ( tempa ) ) ;
 vpx_memcpy ( l , templ , sizeof ( templ ) ) ;
 for ( idy = 0 ;
 idy < num_4x4_blocks_high * 4 ;
 ++ idy ) vpx_memcpy ( best_dst + idy * 8 , dst_init + idy * dst_stride , num_4x4_blocks_wide * 4 ) ;
 }
 next : {
 }
 }
 if ( best_rd >= rd_thresh || x -> skip_encode ) return best_rd ;
 for ( idy = 0 ;
 idy < num_4x4_blocks_high * 4 ;
 ++ idy ) vpx_memcpy ( dst_init + idy * dst_stride , best_dst + idy * 8 , num_4x4_blocks_wide * 4 ) ;
 return best_rd ;
 }