static void encode_superblock ( VP9_COMP * cpi , TOKENEXTRA * * t , int output_enabled , int mi_row , int mi_col , BLOCK_SIZE bsize , PICK_MODE_CONTEXT * ctx ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCK * const x = & cpi -> mb ;
 MACROBLOCKD * const xd = & x -> e_mbd ;
 MODE_INFO * * mi_8x8 = xd -> mi ;
 MODE_INFO * mi = mi_8x8 [ 0 ] ;
 MB_MODE_INFO * mbmi = & mi -> mbmi ;
 const int seg_skip = vp9_segfeature_active ( & cm -> seg , mbmi -> segment_id , SEG_LVL_SKIP ) ;
 const int mis = cm -> mi_stride ;
 const int mi_width = num_8x8_blocks_wide_lookup [ bsize ] ;
 const int mi_height = num_8x8_blocks_high_lookup [ bsize ] ;
 x -> skip_recode = ! x -> select_tx_size && mbmi -> sb_type >= BLOCK_8X8 && cpi -> oxcf . aq_mode != COMPLEXITY_AQ && cpi -> oxcf . aq_mode != CYCLIC_REFRESH_AQ && cpi -> sf . allow_skip_recode ;
 if ( ! x -> skip_recode && ! cpi -> sf . use_nonrd_pick_mode ) vpx_memset ( x -> skip_txfm , 0 , sizeof ( x -> skip_txfm ) ) ;
 x -> skip_optimize = ctx -> is_coded ;
 ctx -> is_coded = 1 ;
 x -> use_lp32x32fdct = cpi -> sf . use_lp32x32fdct ;
 x -> skip_encode = ( ! output_enabled && cpi -> sf . skip_encode_frame && x -> q_index < QIDX_SKIP_THRESH ) ;
 if ( x -> skip_encode ) return ;
 set_ref_ptrs ( cm , xd , mbmi -> ref_frame [ 0 ] , mbmi -> ref_frame [ 1 ] ) ;
 cpi -> zbin_mode_boost = get_zbin_mode_boost ( mbmi , cpi -> zbin_mode_boost_enabled ) ;
 vp9_update_zbin_extra ( cpi , x ) ;
 if ( ! is_inter_block ( mbmi ) ) {
 int plane ;
 mbmi -> skip = 1 ;
 for ( plane = 0 ;
 plane < MAX_MB_PLANE ;
 ++ plane ) vp9_encode_intra_block_plane ( x , MAX ( bsize , BLOCK_8X8 ) , plane ) ;
 if ( output_enabled ) sum_intra_stats ( & cm -> counts , mi ) ;
 vp9_tokenize_sb ( cpi , t , ! output_enabled , MAX ( bsize , BLOCK_8X8 ) ) ;
 }
 else {
 int ref ;
 const int is_compound = has_second_ref ( mbmi ) ;
 for ( ref = 0 ;
 ref < 1 + is_compound ;
 ++ ref ) {
 YV12_BUFFER_CONFIG * cfg = get_ref_frame_buffer ( cpi , mbmi -> ref_frame [ ref ] ) ;
 vp9_setup_pre_planes ( xd , ref , cfg , mi_row , mi_col , & xd -> block_refs [ ref ] -> sf ) ;
 }
 if ( ! cpi -> sf . reuse_inter_pred_sby || seg_skip ) vp9_build_inter_predictors_sby ( xd , mi_row , mi_col , MAX ( bsize , BLOCK_8X8 ) ) ;
 vp9_build_inter_predictors_sbuv ( xd , mi_row , mi_col , MAX ( bsize , BLOCK_8X8 ) ) ;
 if ( ! x -> skip ) {
 mbmi -> skip = 1 ;
 vp9_encode_sb ( x , MAX ( bsize , BLOCK_8X8 ) ) ;
 vp9_tokenize_sb ( cpi , t , ! output_enabled , MAX ( bsize , BLOCK_8X8 ) ) ;
 }
 else {
 mbmi -> skip = 1 ;
 if ( output_enabled && ! seg_skip ) cm -> counts . skip [ vp9_get_skip_context ( xd ) ] [ 1 ] ++ ;
 reset_skip_context ( xd , MAX ( bsize , BLOCK_8X8 ) ) ;
 }
 }
 if ( output_enabled ) {
 if ( cm -> tx_mode == TX_MODE_SELECT && mbmi -> sb_type >= BLOCK_8X8 && ! ( is_inter_block ( mbmi ) && ( mbmi -> skip || seg_skip ) ) ) {
 ++ get_tx_counts ( max_txsize_lookup [ bsize ] , vp9_get_tx_size_context ( xd ) , & cm -> counts . tx ) [ mbmi -> tx_size ] ;
 }
 else {
 int x , y ;
 TX_SIZE tx_size ;
 if ( is_inter_block ( & mi -> mbmi ) ) {
 tx_size = MIN ( tx_mode_to_biggest_tx_size [ cm -> tx_mode ] , max_txsize_lookup [ bsize ] ) ;
 }
 else {
 tx_size = ( bsize >= BLOCK_8X8 ) ? mbmi -> tx_size : TX_4X4 ;
 }
 for ( y = 0 ;
 y < mi_height ;
 y ++ ) for ( x = 0 ;
 x < mi_width ;
 x ++ ) if ( mi_col + x < cm -> mi_cols && mi_row + y < cm -> mi_rows ) mi_8x8 [ mis * y + x ] -> mbmi . tx_size = tx_size ;
 }
 }
 }