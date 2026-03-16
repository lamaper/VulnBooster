static size_t write_compressed_header ( VP9_COMP * cpi , uint8_t * data ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & cpi -> mb . e_mbd ;
 FRAME_CONTEXT * const fc = & cm -> fc ;
 vp9_writer header_bc ;
 vp9_start_encode ( & header_bc , data ) ;
 if ( xd -> lossless ) cm -> tx_mode = ONLY_4X4 ;
 else encode_txfm_probs ( cm , & header_bc ) ;
 update_coef_probs ( cpi , & header_bc ) ;
 update_skip_probs ( cm , & header_bc ) ;
 if ( ! frame_is_intra_only ( cm ) ) {
 int i ;
 for ( i = 0 ;
 i < INTER_MODE_CONTEXTS ;
 ++ i ) prob_diff_update ( vp9_inter_mode_tree , cm -> fc . inter_mode_probs [ i ] , cm -> counts . inter_mode [ i ] , INTER_MODES , & header_bc ) ;
 vp9_zero ( cm -> counts . inter_mode ) ;
 if ( cm -> interp_filter == SWITCHABLE ) update_switchable_interp_probs ( cm , & header_bc ) ;
 for ( i = 0 ;
 i < INTRA_INTER_CONTEXTS ;
 i ++ ) vp9_cond_prob_diff_update ( & header_bc , & fc -> intra_inter_prob [ i ] , cm -> counts . intra_inter [ i ] ) ;
 if ( cm -> allow_comp_inter_inter ) {
 const int use_compound_pred = cm -> reference_mode != SINGLE_REFERENCE ;
 const int use_hybrid_pred = cm -> reference_mode == REFERENCE_MODE_SELECT ;
 vp9_write_bit ( & header_bc , use_compound_pred ) ;
 if ( use_compound_pred ) {
 vp9_write_bit ( & header_bc , use_hybrid_pred ) ;
 if ( use_hybrid_pred ) for ( i = 0 ;
 i < COMP_INTER_CONTEXTS ;
 i ++ ) vp9_cond_prob_diff_update ( & header_bc , & fc -> comp_inter_prob [ i ] , cm -> counts . comp_inter [ i ] ) ;
 }
 }
 if ( cm -> reference_mode != COMPOUND_REFERENCE ) {
 for ( i = 0 ;
 i < REF_CONTEXTS ;
 i ++ ) {
 vp9_cond_prob_diff_update ( & header_bc , & fc -> single_ref_prob [ i ] [ 0 ] , cm -> counts . single_ref [ i ] [ 0 ] ) ;
 vp9_cond_prob_diff_update ( & header_bc , & fc -> single_ref_prob [ i ] [ 1 ] , cm -> counts . single_ref [ i ] [ 1 ] ) ;
 }
 }
 if ( cm -> reference_mode != SINGLE_REFERENCE ) for ( i = 0 ;
 i < REF_CONTEXTS ;
 i ++ ) vp9_cond_prob_diff_update ( & header_bc , & fc -> comp_ref_prob [ i ] , cm -> counts . comp_ref [ i ] ) ;
 for ( i = 0 ;
 i < BLOCK_SIZE_GROUPS ;
 ++ i ) prob_diff_update ( vp9_intra_mode_tree , cm -> fc . y_mode_prob [ i ] , cm -> counts . y_mode [ i ] , INTRA_MODES , & header_bc ) ;
 for ( i = 0 ;
 i < PARTITION_CONTEXTS ;
 ++ i ) prob_diff_update ( vp9_partition_tree , fc -> partition_prob [ i ] , cm -> counts . partition [ i ] , PARTITION_TYPES , & header_bc ) ;
 vp9_write_nmv_probs ( cm , cm -> allow_high_precision_mv , & header_bc ) ;
 }
 vp9_stop_encode ( & header_bc ) ;
 assert ( header_bc . pos <= 0xffff ) ;
 return header_bc . pos ;
 }