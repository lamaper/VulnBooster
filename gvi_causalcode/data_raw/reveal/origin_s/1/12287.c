void vp9_xform_quant_fp ( MACROBLOCK * x , int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size ) {
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const struct macroblock_plane * const p = & x -> plane [ plane ] ;
 const struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 const scan_order * const scan_order = & vp9_default_scan_orders [ tx_size ] ;
 int16_t * const coeff = BLOCK_OFFSET ( p -> coeff , block ) ;
 int16_t * const qcoeff = BLOCK_OFFSET ( p -> qcoeff , block ) ;
 int16_t * const dqcoeff = BLOCK_OFFSET ( pd -> dqcoeff , block ) ;
 uint16_t * const eob = & p -> eobs [ block ] ;
 const int diff_stride = 4 * num_4x4_blocks_wide_lookup [ plane_bsize ] ;
 int i , j ;
 const int16_t * src_diff ;
 txfrm_block_to_raster_xy ( plane_bsize , tx_size , block , & i , & j ) ;
 src_diff = & p -> src_diff [ 4 * ( j * diff_stride + i ) ] ;
 switch ( tx_size ) {
 case TX_32X32 : fdct32x32 ( x -> use_lp32x32fdct , src_diff , coeff , diff_stride ) ;
 vp9_quantize_fp_32x32 ( coeff , 1024 , x -> skip_block , p -> zbin , p -> round_fp , p -> quant_fp , p -> quant_shift , qcoeff , dqcoeff , pd -> dequant , p -> zbin_extra , eob , scan_order -> scan , scan_order -> iscan ) ;
 break ;
 case TX_16X16 : vp9_fdct16x16 ( src_diff , coeff , diff_stride ) ;
 vp9_quantize_fp ( coeff , 256 , x -> skip_block , p -> zbin , p -> round_fp , p -> quant_fp , p -> quant_shift , qcoeff , dqcoeff , pd -> dequant , p -> zbin_extra , eob , scan_order -> scan , scan_order -> iscan ) ;
 break ;
 case TX_8X8 : vp9_fdct8x8 ( src_diff , coeff , diff_stride ) ;
 vp9_quantize_fp ( coeff , 64 , x -> skip_block , p -> zbin , p -> round_fp , p -> quant_fp , p -> quant_shift , qcoeff , dqcoeff , pd -> dequant , p -> zbin_extra , eob , scan_order -> scan , scan_order -> iscan ) ;
 break ;
 case TX_4X4 : x -> fwd_txm4x4 ( src_diff , coeff , diff_stride ) ;
 vp9_quantize_fp ( coeff , 16 , x -> skip_block , p -> zbin , p -> round_fp , p -> quant_fp , p -> quant_shift , qcoeff , dqcoeff , pd -> dequant , p -> zbin_extra , eob , scan_order -> scan , scan_order -> iscan ) ;
 break ;
 default : assert ( 0 ) ;
 break ;
 }
 }