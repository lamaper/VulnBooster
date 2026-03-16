static void write_mb_modes_kf ( const VP9_COMMON * cm , const MACROBLOCKD * xd , MODE_INFO * mi_8x8 , vp9_writer * w ) {
 const struct segmentation * const seg = & cm -> seg ;
 const MODE_INFO * const mi = mi_8x8 ;
 const MODE_INFO * const above_mi = mi_8x8 [ - xd -> mi_stride ] . src_mi ;
 const MODE_INFO * const left_mi = xd -> left_available ? mi_8x8 [ - 1 ] . src_mi : NULL ;
 const MB_MODE_INFO * const mbmi = & mi -> mbmi ;
 const BLOCK_SIZE bsize = mbmi -> sb_type ;
 if ( seg -> update_map ) write_segment_id ( w , seg , mbmi -> segment_id ) ;
 write_skip ( cm , xd , mbmi -> segment_id , mi , w ) ;
 if ( bsize >= BLOCK_8X8 && cm -> tx_mode == TX_MODE_SELECT ) write_selected_tx_size ( cm , xd , mbmi -> tx_size , bsize , w ) ;
 if ( bsize >= BLOCK_8X8 ) {
 write_intra_mode ( w , mbmi -> mode , get_y_mode_probs ( mi , above_mi , left_mi , 0 ) ) ;
 }
 else {
 const int num_4x4_w = num_4x4_blocks_wide_lookup [ bsize ] ;
 const int num_4x4_h = num_4x4_blocks_high_lookup [ bsize ] ;
 int idx , idy ;
 for ( idy = 0 ;
 idy < 2 ;
 idy += num_4x4_h ) {
 for ( idx = 0 ;
 idx < 2 ;
 idx += num_4x4_w ) {
 const int block = idy * 2 + idx ;
 write_intra_mode ( w , mi -> bmi [ block ] . as_mode , get_y_mode_probs ( mi , above_mi , left_mi , block ) ) ;
 }
 }
 }
 write_intra_mode ( w , mbmi -> uv_mode , vp9_kf_uv_mode_prob [ mbmi -> mode ] ) ;
 }