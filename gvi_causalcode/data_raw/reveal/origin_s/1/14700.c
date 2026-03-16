static void encode_nonrd_sb_row ( VP9_COMP * cpi , const TileInfo * const tile , int mi_row , TOKENEXTRA * * tp ) {
 SPEED_FEATURES * const sf = & cpi -> sf ;
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 int mi_col ;
 vpx_memset ( & xd -> left_context , 0 , sizeof ( xd -> left_context ) ) ;
 vpx_memset ( xd -> left_seg_context , 0 , sizeof ( xd -> left_seg_context ) ) ;
 for ( mi_col = tile -> mi_col_start ;
 mi_col < tile -> mi_col_end ;
 mi_col += MI_BLOCK_SIZE ) {
 int dummy_rate = 0 ;
 int64_t dummy_dist = 0 ;
 const int idx_str = cm -> mi_stride * mi_row + mi_col ;
 MODE_INFO * * mi = cm -> mi_grid_visible + idx_str ;
 MODE_INFO * * prev_mi = cm -> prev_mi_grid_visible + idx_str ;
 BLOCK_SIZE bsize ;
 x -> in_static_area = 0 ;
 x -> source_variance = UINT_MAX ;
 vp9_zero ( x -> pred_mv ) ;
 switch ( sf -> partition_search_type ) {
 case VAR_BASED_PARTITION : choose_partitioning ( cpi , tile , mi_row , mi_col ) ;
 nonrd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , BLOCK_64X64 , 1 , & dummy_rate , & dummy_dist , cpi -> pc_root ) ;
 break ;
 case SOURCE_VAR_BASED_PARTITION : set_source_var_based_partition ( cpi , tile , mi , mi_row , mi_col ) ;
 nonrd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , BLOCK_64X64 , 1 , & dummy_rate , & dummy_dist , cpi -> pc_root ) ;
 break ;
 case VAR_BASED_FIXED_PARTITION : case FIXED_PARTITION : bsize = sf -> partition_search_type == FIXED_PARTITION ? sf -> always_this_block_size : get_nonrd_var_based_fixed_partition ( cpi , mi_row , mi_col ) ;
 set_fixed_partitioning ( cpi , tile , mi , mi_row , mi_col , bsize ) ;
 nonrd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , BLOCK_64X64 , 1 , & dummy_rate , & dummy_dist , cpi -> pc_root ) ;
 break ;
 case REFERENCE_PARTITION : if ( sf -> partition_check || ! ( x -> in_static_area = is_background ( cpi , tile , mi_row , mi_col ) ) ) {
 set_modeinfo_offsets ( cm , xd , mi_row , mi_col ) ;
 auto_partition_range ( cpi , tile , mi_row , mi_col , & sf -> min_partition_size , & sf -> max_partition_size ) ;
 nonrd_pick_partition ( cpi , tile , tp , mi_row , mi_col , BLOCK_64X64 , & dummy_rate , & dummy_dist , 1 , INT64_MAX , cpi -> pc_root ) ;
 }
 else {
 copy_partitioning ( cm , mi , prev_mi ) ;
 nonrd_use_partition ( cpi , tile , mi , tp , mi_row , mi_col , BLOCK_64X64 , 1 , & dummy_rate , & dummy_dist , cpi -> pc_root ) ;
 }
 break ;
 default : assert ( 0 ) ;
 break ;
 }
 }
 }