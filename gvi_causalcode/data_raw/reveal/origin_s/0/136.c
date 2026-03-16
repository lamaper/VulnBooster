static void write_uncompressed_header ( VP9_COMP * cpi , struct vp9_write_bit_buffer * wb ) {
 VP9_COMMON * const cm = & cpi -> common ;
 vp9_wb_write_literal ( wb , VP9_FRAME_MARKER , 2 ) ;
 write_profile ( cm -> profile , wb ) ;
 vp9_wb_write_bit ( wb , 0 ) ;
 vp9_wb_write_bit ( wb , cm -> frame_type ) ;
 vp9_wb_write_bit ( wb , cm -> show_frame ) ;
 vp9_wb_write_bit ( wb , cm -> error_resilient_mode ) ;
 if ( cm -> frame_type == KEY_FRAME ) {
 write_sync_code ( wb ) ;
 write_bitdepth_colorspace_sampling ( cm , wb ) ;
 write_frame_size ( cm , wb ) ;
 }
 else {
 if ( ! cm -> show_frame || ( is_two_pass_svc ( cpi ) && cm -> error_resilient_mode == 0 ) ) vp9_wb_write_bit ( wb , cm -> intra_only ) ;
 if ( ! cm -> error_resilient_mode ) vp9_wb_write_literal ( wb , cm -> reset_frame_context , 2 ) ;
 if ( cm -> intra_only ) {
 write_sync_code ( wb ) ;
 if ( cm -> profile > PROFILE_0 ) {
 write_bitdepth_colorspace_sampling ( cm , wb ) ;
 }
 vp9_wb_write_literal ( wb , get_refresh_mask ( cpi ) , REF_FRAMES ) ;
 write_frame_size ( cm , wb ) ;
 }
 else {
 MV_REFERENCE_FRAME ref_frame ;
 vp9_wb_write_literal ( wb , get_refresh_mask ( cpi ) , REF_FRAMES ) ;
 for ( ref_frame = LAST_FRAME ;
 ref_frame <= ALTREF_FRAME ;
 ++ ref_frame ) {
 vp9_wb_write_literal ( wb , get_ref_frame_idx ( cpi , ref_frame ) , REF_FRAMES_LOG2 ) ;
 vp9_wb_write_bit ( wb , cm -> ref_frame_sign_bias [ ref_frame ] ) ;
 }
 write_frame_size_with_refs ( cpi , wb ) ;
 vp9_wb_write_bit ( wb , cm -> allow_high_precision_mv ) ;
 fix_interp_filter ( cm ) ;
 write_interp_filter ( cm -> interp_filter , wb ) ;
 }
 }
 if ( ! cm -> error_resilient_mode ) {
 vp9_wb_write_bit ( wb , cm -> refresh_frame_context ) ;
 vp9_wb_write_bit ( wb , cm -> frame_parallel_decoding_mode ) ;
 }
 vp9_wb_write_literal ( wb , cm -> frame_context_idx , FRAME_CONTEXTS_LOG2 ) ;
 encode_loopfilter ( & cm -> lf , wb ) ;
 encode_quantization ( cm , wb ) ;
 encode_segmentation ( cm , & cpi -> mb . e_mbd , wb ) ;
 write_tile_info ( cm , wb ) ;
 }