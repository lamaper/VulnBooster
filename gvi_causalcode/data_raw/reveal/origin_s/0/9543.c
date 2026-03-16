static void encode_block_intra ( int plane , int block , BLOCK_SIZE plane_bsize , TX_SIZE tx_size , void * arg ) {
 struct encode_b_args * const args = arg ;
 MACROBLOCK * const x = args -> x ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MB_MODE_INFO * mbmi = & xd -> mi [ 0 ] . src_mi -> mbmi ;
 struct macroblock_plane * const p = & x -> plane [ plane ] ;
 struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 tran_low_t * coeff = BLOCK_OFFSET ( p -> coeff , block ) ;
 tran_low_t * qcoeff = BLOCK_OFFSET ( p -> qcoeff , block ) ;
 tran_low_t * dqcoeff = BLOCK_OFFSET ( pd -> dqcoeff , block ) ;
 const scan_order * scan_order ;
 TX_TYPE tx_type ;
 PREDICTION_MODE mode ;
 const int bwl = b_width_log2 ( plane_bsize ) ;
 const int diff_stride = 4 * ( 1 << bwl ) ;
 uint8_t * src , * dst ;
 int16_t * src_diff ;
 uint16_t * eob = & p -> eobs [ block ] ;
 const int src_stride = p -> src . stride ;
 const int dst_stride = pd -> dst . stride ;
 int i , j ;
 txfrm_block_to_raster_xy ( plane_bsize , tx_size , block , & i , & j ) ;
 dst = & pd -> dst . buf [ 4 * ( j * dst_stride + i ) ] ;
 src = & p -> src . buf [ 4 * ( j * src_stride + i ) ] ;
 src_diff = & p -> src_diff [ 4 * ( j * diff_stride + i ) ] ;
 switch ( tx_size ) {
 case TX_32X32 : scan_order = & vp9_default_scan_orders [ TX_32X32 ] ;
 mode = plane == 0 ? mbmi -> mode : mbmi -> uv_mode ;
 vp9_predict_intra_block ( xd , block >> 6 , bwl , TX_32X32 , mode , x -> skip_encode ? src : dst , x -> skip_encode ? src_stride : dst_stride , dst , dst_stride , i , j , plane ) ;
 if ( ! x -> skip_recode ) {
 vp9_subtract_block ( 32 , 32 , src_diff , diff_stride , src , src_stride , dst , dst_stride ) ;
 fdct32x32 ( x -> use_lp32x32fdct , src_diff , coeff , diff_stride ) ;
 vp9_quantize_b_32x32 ( coeff , 1024 , x -> skip_block , p -> zbin , p -> round , p -> quant , p -> quant_shift , qcoeff , dqcoeff , pd -> dequant , p -> zbin_extra , eob , scan_order -> scan , scan_order -> iscan ) ;
 }
 if ( ! x -> skip_encode && * eob ) vp9_idct32x32_add ( dqcoeff , dst , dst_stride , * eob ) ;
 break ;
 case TX_16X16 : tx_type = get_tx_type ( pd -> plane_type , xd ) ;
 scan_order = & vp9_scan_orders [ TX_16X16 ] [ tx_type ] ;
 mode = plane == 0 ? mbmi -> mode : mbmi -> uv_mode ;
 vp9_predict_intra_block ( xd , block >> 4 , bwl , TX_16X16 , mode , x -> skip_encode ? src : dst , x -> skip_encode ? src_stride : dst_stride , dst , dst_stride , i , j , plane ) ;
 if ( ! x -> skip_recode ) {
 vp9_subtract_block ( 16 , 16 , src_diff , diff_stride , src , src_stride , dst , dst_stride ) ;
 vp9_fht16x16 ( src_diff , coeff , diff_stride , tx_type ) ;
 vp9_quantize_b ( coeff , 256 , x -> skip_block , p -> zbin , p -> round , p -> quant , p -> quant_shift , qcoeff , dqcoeff , pd -> dequant , p -> zbin_extra , eob , scan_order -> scan , scan_order -> iscan ) ;
 }
 if ( ! x -> skip_encode && * eob ) vp9_iht16x16_add ( tx_type , dqcoeff , dst , dst_stride , * eob ) ;
 break ;
 case TX_8X8 : tx_type = get_tx_type ( pd -> plane_type , xd ) ;
 scan_order = & vp9_scan_orders [ TX_8X8 ] [ tx_type ] ;
 mode = plane == 0 ? mbmi -> mode : mbmi -> uv_mode ;
 vp9_predict_intra_block ( xd , block >> 2 , bwl , TX_8X8 , mode , x -> skip_encode ? src : dst , x -> skip_encode ? src_stride : dst_stride , dst , dst_stride , i , j , plane ) ;
 if ( ! x -> skip_recode ) {
 vp9_subtract_block ( 8 , 8 , src_diff , diff_stride , src , src_stride , dst , dst_stride ) ;
 vp9_fht8x8 ( src_diff , coeff , diff_stride , tx_type ) ;
 vp9_quantize_b ( coeff , 64 , x -> skip_block , p -> zbin , p -> round , p -> quant , p -> quant_shift , qcoeff , dqcoeff , pd -> dequant , p -> zbin_extra , eob , scan_order -> scan , scan_order -> iscan ) ;
 }
 if ( ! x -> skip_encode && * eob ) vp9_iht8x8_add ( tx_type , dqcoeff , dst , dst_stride , * eob ) ;
 break ;
 case TX_4X4 : tx_type = get_tx_type_4x4 ( pd -> plane_type , xd , block ) ;
 scan_order = & vp9_scan_orders [ TX_4X4 ] [ tx_type ] ;
 mode = plane == 0 ? get_y_mode ( xd -> mi [ 0 ] . src_mi , block ) : mbmi -> uv_mode ;
 vp9_predict_intra_block ( xd , block , bwl , TX_4X4 , mode , x -> skip_encode ? src : dst , x -> skip_encode ? src_stride : dst_stride , dst , dst_stride , i , j , plane ) ;
 if ( ! x -> skip_recode ) {
 vp9_subtract_block ( 4 , 4 , src_diff , diff_stride , src , src_stride , dst , dst_stride ) ;
 if ( tx_type != DCT_DCT ) vp9_fht4x4 ( src_diff , coeff , diff_stride , tx_type ) ;
 else x -> fwd_txm4x4 ( src_diff , coeff , diff_stride ) ;
 vp9_quantize_b ( coeff , 16 , x -> skip_block , p -> zbin , p -> round , p -> quant , p -> quant_shift , qcoeff , dqcoeff , pd -> dequant , p -> zbin_extra , eob , scan_order -> scan , scan_order -> iscan ) ;
 }
 if ( ! x -> skip_encode && * eob ) {
 if ( tx_type == DCT_DCT ) x -> itxm_add ( dqcoeff , dst , dst_stride , * eob ) ;
 else vp9_iht4x4_16_add ( dqcoeff , dst , dst_stride , tx_type ) ;
 }
 break ;
 default : assert ( 0 ) ;
 break ;
 }
 if ( * eob ) * ( args -> skip ) = 0 ;
 }