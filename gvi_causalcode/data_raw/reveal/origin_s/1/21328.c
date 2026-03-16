static void dec_build_inter_predictors ( MACROBLOCKD * xd , int plane , int block , int bw , int bh , int x , int y , int w , int h , int mi_x , int mi_y ) {
 struct macroblockd_plane * const pd = & xd -> plane [ plane ] ;
 const MODE_INFO * mi = xd -> mi [ 0 ] ;
 const int is_compound = has_second_ref ( & mi -> mbmi ) ;
 const InterpKernel * kernel = vp9_get_interp_kernel ( mi -> mbmi . interp_filter ) ;
 int ref ;
 for ( ref = 0 ;
 ref < 1 + is_compound ;
 ++ ref ) {
 const struct scale_factors * const sf = & xd -> block_refs [ ref ] -> sf ;
 struct buf_2d * const pre_buf = & pd -> pre [ ref ] ;
 struct buf_2d * const dst_buf = & pd -> dst ;
 uint8_t * const dst = dst_buf -> buf + dst_buf -> stride * y + x ;
 const MV mv = mi -> mbmi . sb_type < BLOCK_8X8 ? average_split_mvs ( pd , mi , ref , block ) : mi -> mbmi . mv [ ref ] . as_mv ;
 const MV mv_q4 = clamp_mv_to_umv_border_sb ( xd , & mv , bw , bh , pd -> subsampling_x , pd -> subsampling_y ) ;
 MV32 scaled_mv ;
 int xs , ys , x0 , y0 , x0_16 , y0_16 , frame_width , frame_height , buf_stride , subpel_x , subpel_y ;
 uint8_t * ref_frame , * buf_ptr ;
 const YV12_BUFFER_CONFIG * ref_buf = xd -> block_refs [ ref ] -> buf ;
 if ( plane == 0 ) {
 frame_width = ref_buf -> y_crop_width ;
 frame_height = ref_buf -> y_crop_height ;
 ref_frame = ref_buf -> y_buffer ;
 }
 else {
 frame_width = ref_buf -> uv_crop_width ;
 frame_height = ref_buf -> uv_crop_height ;
 ref_frame = plane == 1 ? ref_buf -> u_buffer : ref_buf -> v_buffer ;
 }
 if ( vp9_is_scaled ( sf ) ) {
 int x_start = ( - xd -> mb_to_left_edge >> ( 3 + pd -> subsampling_x ) ) ;
 int y_start = ( - xd -> mb_to_top_edge >> ( 3 + pd -> subsampling_y ) ) ;
 x0_16 = ( x_start + x ) << SUBPEL_BITS ;
 y0_16 = ( y_start + y ) << SUBPEL_BITS ;
 x0_16 = sf -> scale_value_x ( x0_16 , sf ) ;
 y0_16 = sf -> scale_value_y ( y0_16 , sf ) ;
 x0 = sf -> scale_value_x ( x_start + x , sf ) ;
 y0 = sf -> scale_value_y ( y_start + y , sf ) ;
 scaled_mv = vp9_scale_mv ( & mv_q4 , mi_x + x , mi_y + y , sf ) ;
 xs = sf -> x_step_q4 ;
 ys = sf -> y_step_q4 ;
 }
 else {
 x0 = ( - xd -> mb_to_left_edge >> ( 3 + pd -> subsampling_x ) ) + x ;
 y0 = ( - xd -> mb_to_top_edge >> ( 3 + pd -> subsampling_y ) ) + y ;
 x0_16 = x0 << SUBPEL_BITS ;
 y0_16 = y0 << SUBPEL_BITS ;
 scaled_mv . row = mv_q4 . row ;
 scaled_mv . col = mv_q4 . col ;
 xs = ys = 16 ;
 }
 subpel_x = scaled_mv . col & SUBPEL_MASK ;
 subpel_y = scaled_mv . row & SUBPEL_MASK ;
 x0 += scaled_mv . col >> SUBPEL_BITS ;
 y0 += scaled_mv . row >> SUBPEL_BITS ;
 x0_16 += scaled_mv . col ;
 y0_16 += scaled_mv . row ;
 buf_ptr = ref_frame + y0 * pre_buf -> stride + x0 ;
 buf_stride = pre_buf -> stride ;
 if ( scaled_mv . col || scaled_mv . row || ( frame_width & 0x7 ) || ( frame_height & 0x7 ) ) {
 int x1 = ( ( x0_16 + ( w - 1 ) * xs ) >> SUBPEL_BITS ) + 1 ;
 int y1 = ( ( y0_16 + ( h - 1 ) * ys ) >> SUBPEL_BITS ) + 1 ;
 int x_pad = 0 , y_pad = 0 ;
 if ( subpel_x || ( sf -> x_step_q4 & SUBPEL_MASK ) ) {
 x0 -= VP9_INTERP_EXTEND - 1 ;
 x1 += VP9_INTERP_EXTEND ;
 x_pad = 1 ;
 }
 if ( subpel_y || ( sf -> y_step_q4 & SUBPEL_MASK ) ) {
 y0 -= VP9_INTERP_EXTEND - 1 ;
 y1 += VP9_INTERP_EXTEND ;
 y_pad = 1 ;
 }
 if ( x0 < 0 || x0 > frame_width - 1 || x1 < 0 || x1 > frame_width - 1 || y0 < 0 || y0 > frame_height - 1 || y1 < 0 || y1 > frame_height - 1 ) {
 uint8_t * buf_ptr1 = ref_frame + y0 * pre_buf -> stride + x0 ;
 build_mc_border ( buf_ptr1 , pre_buf -> stride , xd -> mc_buf , x1 - x0 + 1 , x0 , y0 , x1 - x0 + 1 , y1 - y0 + 1 , frame_width , frame_height ) ;
 buf_stride = x1 - x0 + 1 ;
 buf_ptr = xd -> mc_buf + y_pad * 3 * buf_stride + x_pad * 3 ;
 }
 }
 inter_predictor ( buf_ptr , buf_stride , dst , dst_buf -> stride , subpel_x , subpel_y , sf , w , h , ref , kernel , xs , ys ) ;
 }
 }