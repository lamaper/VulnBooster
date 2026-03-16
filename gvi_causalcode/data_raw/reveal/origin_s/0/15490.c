static int64_t encode_inter_mb_segment ( VP9_COMP * cpi , MACROBLOCK * x , int64_t best_yrd , int i , int * labelyrate , int64_t * distortion , int64_t * sse , ENTROPY_CONTEXT * ta , ENTROPY_CONTEXT * tl , int mi_row , int mi_col ) {
 int k ;
 MACROBLOCKD * xd = & x -> e_mbd ;
 struct macroblockd_plane * const pd = & xd -> plane [ 0 ] ;
 struct macroblock_plane * const p = & x -> plane [ 0 ] ;
 MODE_INFO * const mi = xd -> mi [ 0 ] . src_mi ;
 const BLOCK_SIZE plane_bsize = get_plane_block_size ( mi -> mbmi . sb_type , pd ) ;
 const int width = 4 * num_4x4_blocks_wide_lookup [ plane_bsize ] ;
 const int height = 4 * num_4x4_blocks_high_lookup [ plane_bsize ] ;
 int idx , idy ;
 const uint8_t * const src = & p -> src . buf [ raster_block_offset ( BLOCK_8X8 , i , p -> src . stride ) ] ;
 uint8_t * const dst = & pd -> dst . buf [ raster_block_offset ( BLOCK_8X8 , i , pd -> dst . stride ) ] ;
 int64_t thisdistortion = 0 , thissse = 0 ;
 int thisrate = 0 , ref ;
 const scan_order * so = & vp9_default_scan_orders [ TX_4X4 ] ;
 const int is_compound = has_second_ref ( & mi -> mbmi ) ;
 const InterpKernel * kernel = vp9_get_interp_kernel ( mi -> mbmi . interp_filter ) ;
 for ( ref = 0 ;
 ref < 1 + is_compound ;
 ++ ref ) {
 const uint8_t * pre = & pd -> pre [ ref ] . buf [ raster_block_offset ( BLOCK_8X8 , i , pd -> pre [ ref ] . stride ) ] ;
 vp9_build_inter_predictor ( pre , pd -> pre [ ref ] . stride , dst , pd -> dst . stride , & mi -> bmi [ i ] . as_mv [ ref ] . as_mv , & xd -> block_refs [ ref ] -> sf , width , height , ref , kernel , MV_PRECISION_Q3 , mi_col * MI_SIZE + 4 * ( i % 2 ) , mi_row * MI_SIZE + 4 * ( i / 2 ) ) ;
 }
 vp9_subtract_block ( height , width , raster_block_offset_int16 ( BLOCK_8X8 , i , p -> src_diff ) , 8 , src , p -> src . stride , dst , pd -> dst . stride ) ;
 k = i ;
 for ( idy = 0 ;
 idy < height / 4 ;
 ++ idy ) {
 for ( idx = 0 ;
 idx < width / 4 ;
 ++ idx ) {
 int64_t ssz , rd , rd1 , rd2 ;
 tran_low_t * coeff ;
 k += ( idy * 2 + idx ) ;
 coeff = BLOCK_OFFSET ( p -> coeff , k ) ;
 x -> fwd_txm4x4 ( raster_block_offset_int16 ( BLOCK_8X8 , k , p -> src_diff ) , coeff , 8 ) ;
 vp9_regular_quantize_b_4x4 ( x , 0 , k , so -> scan , so -> iscan ) ;
 thisdistortion += vp9_block_error ( coeff , BLOCK_OFFSET ( pd -> dqcoeff , k ) , 16 , & ssz ) ;
 thissse += ssz ;
 thisrate += cost_coeffs ( x , 0 , k , ta + ( k & 1 ) , tl + ( k >> 1 ) , TX_4X4 , so -> scan , so -> neighbors , cpi -> sf . use_fast_coef_costing ) ;
 rd1 = RDCOST ( x -> rdmult , x -> rddiv , thisrate , thisdistortion >> 2 ) ;
 rd2 = RDCOST ( x -> rdmult , x -> rddiv , 0 , thissse >> 2 ) ;
 rd = MIN ( rd1 , rd2 ) ;
 if ( rd >= best_yrd ) return INT64_MAX ;
 }
 }
 * distortion = thisdistortion >> 2 ;
 * labelyrate = thisrate ;
 * sse = thissse >> 2 ;
 return RDCOST ( x -> rdmult , x -> rddiv , * labelyrate , * distortion ) ;
 }