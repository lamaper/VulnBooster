void vp9_xform_quant_dc ( MACROBLOCK * x , int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size ) {
 MACROBLOCKD * const xd = & x -> e_mbd ;
 const struct macroblock_plane * const p = & x -> plane [ plane ] ;
 const struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
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
 case TX_32X32 : vp9_fdct32x32_1 ( src_diff , coeff , diff_stride ) ;
 vp9_quantize_dc_32x32 ( coeff , x -> skip_block , p -> round , p -> quant_fp [ 0 ] , qcoeff , dqcoeff , pd -> dequant [ 0 ] , eob ) ;
 break ;
 case TX_16X16 : vp9_fdct16x16_1 ( src_diff , coeff , diff_stride ) ;
 vp9_quantize_dc ( coeff , x -> skip_block , p -> round , p -> quant_fp [ 0 ] , qcoeff , dqcoeff , pd -> dequant [ 0 ] , eob ) ;
 break ;
 case TX_8X8 : vp9_fdct8x8_1 ( src_diff , coeff , diff_stride ) ;
 vp9_quantize_dc ( coeff , x -> skip_block , p -> round , p -> quant_fp [ 0 ] , qcoeff , dqcoeff , pd -> dequant [ 0 ] , eob ) ;
 break ;
 case TX_4X4 : x -> fwd_txm4x4 ( src_diff , coeff , diff_stride ) ;
 vp9_quantize_dc ( coeff , x -> skip_block , p -> round , p -> quant_fp [ 0 ] , qcoeff , dqcoeff , pd -> dequant [ 0 ] , eob ) ;
 break ;
 default : assert ( 0 ) ;
 break ;
 }
 }