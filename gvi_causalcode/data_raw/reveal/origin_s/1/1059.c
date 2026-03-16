static void build_inter_predictors ( MACROBLOCKD * xd , int plane , int block , int bw , int bh , int x , int y , int w , int h , int mi_x , int mi_y ) {
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
 uint8_t * pre ;
 MV32 scaled_mv ;
 int xs , ys , subpel_x , subpel_y ;
 if ( vp9_is_scaled ( sf ) ) {
 pre = pre_buf -> buf + scaled_buffer_offset ( x , y , pre_buf -> stride , sf ) ;
 scaled_mv = vp9_scale_mv ( & mv_q4 , mi_x + x , mi_y + y , sf ) ;
 xs = sf -> x_step_q4 ;
 ys = sf -> y_step_q4 ;
 }
 else {
 pre = pre_buf -> buf + ( y * pre_buf -> stride + x ) ;
 scaled_mv . row = mv_q4 . row ;
 scaled_mv . col = mv_q4 . col ;
 xs = ys = 16 ;
 }
 subpel_x = scaled_mv . col & SUBPEL_MASK ;
 subpel_y = scaled_mv . row & SUBPEL_MASK ;
 pre += ( scaled_mv . row >> SUBPEL_BITS ) * pre_buf -> stride + ( scaled_mv . col >> SUBPEL_BITS ) ;
 inter_predictor ( pre , pre_buf -> stride , dst , dst_buf -> stride , subpel_x , subpel_y , sf , w , h , ref , kernel , xs , ys ) ;
 }
 }