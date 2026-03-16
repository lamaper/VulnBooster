static void encode_rd_sb_row ( VP9_COMP * cpi , const TileInfo * const tile , int mi_row , TOKENEXTRA * * tp ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & cpi -> mb . e_mbd ;
 SPEED_FEATURES * const sf = & cpi -> sf ;
 int mi_col ;
 vpx_memset ( & xd -> left_context , 0 , sizeof ( xd -> left_context ) ) ;
 vpx_memset ( xd -> left_seg_context , 0 , sizeof ( xd -> left_seg_context ) ) ;
 for ( mi_col = tile -> mi_col_start ;
 mi_col < tile -> mi_col_end ;
 mi_col += MI_BLOCK_SIZE ) {
 int dummy_rate ;
 int64_t dummy_dist ;
 int i ;
 if ( sf -> adaptive_pred_interp_filter ) {
 for ( i = 0 ;
 i < 64 ;
 ++ i ) cpi -> leaf_tree [ i ] . pred_interp_filter = SWITCHABLE ;
 for ( i = 0 ;
 i < 64 ;
 ++ i ) {
 cpi -> pc_tree [ i ] . vertical [ 0 ] . pred_interp_filter = SWITCHABLE ;
 cpi -> pc_tree [ i ] . vertical [ 1 ] . pred_interp_filter = SWITCHABLE ;
 cpi -> pc_tree [ i ] . horizontal [ 0 ] . pred_interp_filter = SWITCHABLE ;
 cpi -> pc_tree [ i ] . horizontal [ 1 ] . pred_interp_filter = SWITCHABLE ;
 }
 }
 vp9_zero ( cpi -> mb . pred_mv ) ;
 cpi -> pc_root -> index = 0 ;
 if ( ( sf -> partition_search_type == SEARCH_PARTITION && sf -> use_lastframe_partitioning ) || sf -> partition_search_type == FIXED_PARTITION || sf -> partition_search_type == VAR_BASED_PARTITION || sf -> partition_search_type == VAR_BASED_FIXED_PARTITION ) {
 const int idx_str = cm -> mi_stride * mi_row + mi_col ;
 MODE_INFO * mi = cm -> mi + idx_str ;
 MODE_INFO * prev_mi = ( cm -> prev_mip + cm -> mi_stride + 1 + idx_str ) -> src_mi ;
 cpi -> mb . source_variance = UINT_MAX ;
 if ( sf -> partition_search_type == FIXED_PARTITION ) {
 set_offsets ( cpi , tile , mi_row , mi_col , BLOCK_64X64 ) ;
 set_fixed_partitioning ( cpi , tile , mi , mi_row , mi_col , sf -> always_this_block_size ) ;
 rd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , BLOCK_64X64 , & dummy_rate , & dummy_dist , 1 , cpi -> pc_root ) ;
 }
 else if ( cpi -> skippable_frame || sf -> partition_search_type == VAR_BASED_FIXED_PARTITION ) {
 BLOCK_SIZE bsize ;
 set_offsets ( cpi , tile , mi_row , mi_col , BLOCK_64X64 ) ;
 bsize = get_rd_var_based_fixed_partition ( cpi , mi_row , mi_col ) ;
 set_fixed_partitioning ( cpi , tile , mi , mi_row , mi_col , bsize ) ;
 rd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , BLOCK_64X64 , & dummy_rate , & dummy_dist , 1 , cpi -> pc_root ) ;
 }
 else if ( sf -> partition_search_type == VAR_BASED_PARTITION ) {
 choose_partitioning ( cpi , tile , mi_row , mi_col ) ;
 rd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , BLOCK_64X64 , & dummy_rate , & dummy_dist , 1 , cpi -> pc_root ) ;
 }
 else {
 GF_GROUP * gf_grp = & cpi -> twopass . gf_group ;
 int last_was_mid_sequence_overlay = 0 ;
 if ( ( cpi -> oxcf . pass == 2 ) && ( gf_grp -> index ) ) {
 if ( gf_grp -> update_type [ gf_grp -> index - 1 ] == OVERLAY_UPDATE ) last_was_mid_sequence_overlay = 1 ;
 }
 if ( ( cpi -> rc . frames_since_key % sf -> last_partitioning_redo_frequency ) == 0 || last_was_mid_sequence_overlay || cm -> prev_mi == 0 || cm -> show_frame == 0 || cm -> frame_type == KEY_FRAME || cpi -> rc . is_src_frame_alt_ref || ( ( sf -> use_lastframe_partitioning == LAST_FRAME_PARTITION_LOW_MOTION ) && sb_has_motion ( cm , prev_mi , sf -> lf_motion_threshold ) ) ) {
 if ( sf -> auto_min_max_partition_size ) {
 set_offsets ( cpi , tile , mi_row , mi_col , BLOCK_64X64 ) ;
 rd_auto_partition_range ( cpi , tile , mi_row , mi_col , & sf -> min_partition_size , & sf -> max_partition_size ) ;
 }
 rd_pick_partition ( cpi , tile , tp , mi_row , mi_col , BLOCK_64X64 , & dummy_rate , & dummy_dist , INT64_MAX , cpi -> pc_root ) ;
 }
 else {
 if ( sf -> constrain_copy_partition && sb_has_motion ( cm , prev_mi , sf -> lf_motion_threshold ) ) constrain_copy_partitioning ( cpi , tile , mi , prev_mi , mi_row , mi_col , BLOCK_16X16 ) ;
 else copy_partitioning ( cm , mi , prev_mi ) ;
 rd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , BLOCK_64X64 , & dummy_rate , & dummy_dist , 1 , cpi -> pc_root ) ;
 }
 }
 }
 else {
 if ( sf -> auto_min_max_partition_size ) {
 set_offsets ( cpi , tile , mi_row , mi_col , BLOCK_64X64 ) ;
 rd_auto_partition_range ( cpi , tile , mi_row , mi_col , & sf -> min_partition_size , & sf -> max_partition_size ) ;
 }
 rd_pick_partition ( cpi , tile , tp , mi_row , mi_col , BLOCK_64X64 , & dummy_rate , & dummy_dist , INT64_MAX , cpi -> pc_root ) ;
 }
 }
 }