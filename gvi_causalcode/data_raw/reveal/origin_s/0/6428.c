static int read_compressed_header ( VP9Decoder * pbi , const uint8_t * data , size_t partition_size ) {
 VP9_COMMON * const cm = & pbi -> common ;
 MACROBLOCKD * const xd = & pbi -> mb ;
 FRAME_CONTEXT * const fc = & cm -> fc ;
 vp9_reader r ;
 int k ;
 if ( vp9_reader_init ( & r , data , partition_size , pbi -> decrypt_cb , pbi -> decrypt_state ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_MEM_ERROR , "Failed to allocate bool decoder 0" ) ;
 cm -> tx_mode = xd -> lossless ? ONLY_4X4 : read_tx_mode ( & r ) ;
 if ( cm -> tx_mode == TX_MODE_SELECT ) read_tx_mode_probs ( & fc -> tx_probs , & r ) ;
 read_coef_probs ( fc , cm -> tx_mode , & r ) ;
 for ( k = 0 ;
 k < SKIP_CONTEXTS ;
 ++ k ) vp9_diff_update_prob ( & r , & fc -> skip_probs [ k ] ) ;
 if ( ! frame_is_intra_only ( cm ) ) {
 nmv_context * const nmvc = & fc -> nmvc ;
 int i , j ;
 read_inter_mode_probs ( fc , & r ) ;
 if ( cm -> interp_filter == SWITCHABLE ) read_switchable_interp_probs ( fc , & r ) ;
 for ( i = 0 ;
 i < INTRA_INTER_CONTEXTS ;
 i ++ ) vp9_diff_update_prob ( & r , & fc -> intra_inter_prob [ i ] ) ;
 cm -> reference_mode = read_frame_reference_mode ( cm , & r ) ;
 if ( cm -> reference_mode != SINGLE_REFERENCE ) setup_compound_reference_mode ( cm ) ;
 read_frame_reference_mode_probs ( cm , & r ) ;
 for ( j = 0 ;
 j < BLOCK_SIZE_GROUPS ;
 j ++ ) for ( i = 0 ;
 i < INTRA_MODES - 1 ;
 ++ i ) vp9_diff_update_prob ( & r , & fc -> y_mode_prob [ j ] [ i ] ) ;
 for ( j = 0 ;
 j < PARTITION_CONTEXTS ;
 ++ j ) for ( i = 0 ;
 i < PARTITION_TYPES - 1 ;
 ++ i ) vp9_diff_update_prob ( & r , & fc -> partition_prob [ j ] [ i ] ) ;
 read_mv_probs ( nmvc , cm -> allow_high_precision_mv , & r ) ;
 }
 return vp9_reader_has_error ( & r ) ;
 }