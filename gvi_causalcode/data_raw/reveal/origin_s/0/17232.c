static void pack_inter_mode_mvs ( VP9_COMP * cpi , const MODE_INFO * mi , vp9_writer * w ) {
 VP9_COMMON * const cm = & cpi -> common ;
 const nmv_context * nmvc = & cm -> fc . nmvc ;
 const MACROBLOCK * const x = & cpi -> mb ;
 const MACROBLOCKD * const xd = & x -> e_mbd ;
 const struct segmentation * const seg = & cm -> seg ;
 const MB_MODE_INFO * const mbmi = & mi -> mbmi ;
 const PREDICTION_MODE mode = mbmi -> mode ;
 const int segment_id = mbmi -> segment_id ;
 const BLOCK_SIZE bsize = mbmi -> sb_type ;
 const int allow_hp = cm -> allow_high_precision_mv ;
 const int is_inter = is_inter_block ( mbmi ) ;
 const int is_compound = has_second_ref ( mbmi ) ;
 int skip , ref ;
 if ( seg -> update_map ) {
 if ( seg -> temporal_update ) {
 const int pred_flag = mbmi -> seg_id_predicted ;
 vp9_prob pred_prob = vp9_get_pred_prob_seg_id ( seg , xd ) ;
 vp9_write ( w , pred_flag , pred_prob ) ;
 if ( ! pred_flag ) write_segment_id ( w , seg , segment_id ) ;
 }
 else {
 write_segment_id ( w , seg , segment_id ) ;
 }
 }
 skip = write_skip ( cm , xd , segment_id , mi , w ) ;
 if ( ! vp9_segfeature_active ( seg , segment_id , SEG_LVL_REF_FRAME ) ) vp9_write ( w , is_inter , vp9_get_intra_inter_prob ( cm , xd ) ) ;
 if ( bsize >= BLOCK_8X8 && cm -> tx_mode == TX_MODE_SELECT && ! ( is_inter && ( skip || vp9_segfeature_active ( seg , segment_id , SEG_LVL_SKIP ) ) ) ) {
 write_selected_tx_size ( cm , xd , mbmi -> tx_size , bsize , w ) ;
 }
 if ( ! is_inter ) {
 if ( bsize >= BLOCK_8X8 ) {
 write_intra_mode ( w , mode , cm -> fc . y_mode_prob [ size_group_lookup [ bsize ] ] ) ;
 }
 else {
 int idx , idy ;
 const int num_4x4_w = num_4x4_blocks_wide_lookup [ bsize ] ;
 const int num_4x4_h = num_4x4_blocks_high_lookup [ bsize ] ;
 for ( idy = 0 ;
 idy < 2 ;
 idy += num_4x4_h ) {
 for ( idx = 0 ;
 idx < 2 ;
 idx += num_4x4_w ) {
 const PREDICTION_MODE b_mode = mi -> bmi [ idy * 2 + idx ] . as_mode ;
 write_intra_mode ( w , b_mode , cm -> fc . y_mode_prob [ 0 ] ) ;
 }
 }
 }
 write_intra_mode ( w , mbmi -> uv_mode , cm -> fc . uv_mode_prob [ mode ] ) ;
 }
 else {
 const int mode_ctx = mbmi -> mode_context [ mbmi -> ref_frame [ 0 ] ] ;
 const vp9_prob * const inter_probs = cm -> fc . inter_mode_probs [ mode_ctx ] ;
 write_ref_frames ( cm , xd , w ) ;
 if ( ! vp9_segfeature_active ( seg , segment_id , SEG_LVL_SKIP ) ) {
 if ( bsize >= BLOCK_8X8 ) {
 write_inter_mode ( w , mode , inter_probs ) ;
 ++ cm -> counts . inter_mode [ mode_ctx ] [ INTER_OFFSET ( mode ) ] ;
 }
 }
 if ( cm -> interp_filter == SWITCHABLE ) {
 const int ctx = vp9_get_pred_context_switchable_interp ( xd ) ;
 vp9_write_token ( w , vp9_switchable_interp_tree , cm -> fc . switchable_interp_prob [ ctx ] , & switchable_interp_encodings [ mbmi -> interp_filter ] ) ;
 ++ cpi -> interp_filter_selected [ 0 ] [ mbmi -> interp_filter ] ;
 }
 else {
 assert ( mbmi -> interp_filter == cm -> interp_filter ) ;
 }
 if ( bsize < BLOCK_8X8 ) {
 const int num_4x4_w = num_4x4_blocks_wide_lookup [ bsize ] ;
 const int num_4x4_h = num_4x4_blocks_high_lookup [ bsize ] ;
 int idx , idy ;
 for ( idy = 0 ;
 idy < 2 ;
 idy += num_4x4_h ) {
 for ( idx = 0 ;
 idx < 2 ;
 idx += num_4x4_w ) {
 const int j = idy * 2 + idx ;
 const PREDICTION_MODE b_mode = mi -> bmi [ j ] . as_mode ;
 write_inter_mode ( w , b_mode , inter_probs ) ;
 ++ cm -> counts . inter_mode [ mode_ctx ] [ INTER_OFFSET ( b_mode ) ] ;
 if ( b_mode == NEWMV ) {
 for ( ref = 0 ;
 ref < 1 + is_compound ;
 ++ ref ) vp9_encode_mv ( cpi , w , & mi -> bmi [ j ] . as_mv [ ref ] . as_mv , & mbmi -> ref_mvs [ mbmi -> ref_frame [ ref ] ] [ 0 ] . as_mv , nmvc , allow_hp ) ;
 }
 }
 }
 }
 else {
 if ( mode == NEWMV ) {
 for ( ref = 0 ;
 ref < 1 + is_compound ;
 ++ ref ) vp9_encode_mv ( cpi , w , & mbmi -> mv [ ref ] . as_mv , & mbmi -> ref_mvs [ mbmi -> ref_frame [ ref ] ] [ 0 ] . as_mv , nmvc , allow_hp ) ;
 }
 }
 }
 }