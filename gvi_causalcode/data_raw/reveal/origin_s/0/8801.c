static size_t read_uncompressed_header ( VP9Decoder * pbi , struct vp9_read_bit_buffer * rb ) {
 VP9_COMMON * const cm = & pbi -> common ;
 size_t sz ;
 int i ;
 cm -> last_frame_type = cm -> frame_type ;
 if ( vp9_rb_read_literal ( rb , 2 ) != VP9_FRAME_MARKER ) vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "Invalid frame marker" ) ;
 cm -> profile = read_profile ( rb ) ;
 if ( cm -> profile >= MAX_PROFILES ) vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "Unsupported bitstream profile" ) ;
 cm -> show_existing_frame = vp9_rb_read_bit ( rb ) ;
 if ( cm -> show_existing_frame ) {
 const int frame_to_show = cm -> ref_frame_map [ vp9_rb_read_literal ( rb , 3 ) ] ;
 if ( frame_to_show < 0 || cm -> frame_bufs [ frame_to_show ] . ref_count < 1 ) vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "Buffer %d does not contain a decoded frame" , frame_to_show ) ;
 ref_cnt_fb ( cm -> frame_bufs , & cm -> new_fb_idx , frame_to_show ) ;
 pbi -> refresh_frame_flags = 0 ;
 cm -> lf . filter_level = 0 ;
 cm -> show_frame = 1 ;
 return 0 ;
 }
 cm -> frame_type = ( FRAME_TYPE ) vp9_rb_read_bit ( rb ) ;
 cm -> show_frame = vp9_rb_read_bit ( rb ) ;
 cm -> error_resilient_mode = vp9_rb_read_bit ( rb ) ;
 if ( cm -> frame_type == KEY_FRAME ) {
 if ( ! vp9_read_sync_code ( rb ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "Invalid frame sync code" ) ;
 if ( cm -> profile > PROFILE_1 ) cm -> bit_depth = vp9_rb_read_bit ( rb ) ? BITS_12 : BITS_10 ;
 cm -> color_space = ( COLOR_SPACE ) vp9_rb_read_literal ( rb , 3 ) ;
 if ( cm -> color_space != SRGB ) {
 vp9_rb_read_bit ( rb ) ;
 if ( cm -> profile >= PROFILE_1 ) {
 cm -> subsampling_x = vp9_rb_read_bit ( rb ) ;
 cm -> subsampling_y = vp9_rb_read_bit ( rb ) ;
 vp9_rb_read_bit ( rb ) ;
 }
 else {
 cm -> subsampling_y = cm -> subsampling_x = 1 ;
 }
 }
 else {
 if ( cm -> profile >= PROFILE_1 ) {
 cm -> subsampling_y = cm -> subsampling_x = 0 ;
 vp9_rb_read_bit ( rb ) ;
 }
 else {
 vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "RGB not supported in profile 0" ) ;
 }
 }
 pbi -> refresh_frame_flags = ( 1 << REF_FRAMES ) - 1 ;
 for ( i = 0 ;
 i < REFS_PER_FRAME ;
 ++ i ) {
 cm -> frame_refs [ i ] . idx = cm -> new_fb_idx ;
 cm -> frame_refs [ i ] . buf = get_frame_new_buffer ( cm ) ;
 }
 setup_frame_size ( cm , rb ) ;
 }
 else {
 cm -> intra_only = cm -> show_frame ? 0 : vp9_rb_read_bit ( rb ) ;
 cm -> reset_frame_context = cm -> error_resilient_mode ? : vp9_rb_read_literal ( rb , 2 ) ;
 if ( cm -> intra_only ) {
 if ( ! vp9_read_sync_code ( rb ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_UNSUP_BITSTREAM , "Invalid frame sync code" ) ;
 pbi -> refresh_frame_flags = vp9_rb_read_literal ( rb , REF_FRAMES ) ;
 cm -> color_space = BT_601 ;
 cm -> subsampling_y = cm -> subsampling_x = 1 ;
 setup_frame_size ( cm , rb ) ;
 }
 else {
 pbi -> refresh_frame_flags = vp9_rb_read_literal ( rb , REF_FRAMES ) ;
 for ( i = 0 ;
 i < REFS_PER_FRAME ;
 ++ i ) {
 const int ref = vp9_rb_read_literal ( rb , REF_FRAMES_LOG2 ) ;
 const int idx = cm -> ref_frame_map [ ref ] ;
 RefBuffer * const ref_frame = & cm -> frame_refs [ i ] ;
 ref_frame -> idx = idx ;
 ref_frame -> buf = & cm -> frame_bufs [ idx ] . buf ;
 cm -> ref_frame_sign_bias [ LAST_FRAME + i ] = vp9_rb_read_bit ( rb ) ;
 }
 setup_frame_size_with_refs ( cm , rb ) ;
 cm -> allow_high_precision_mv = vp9_rb_read_bit ( rb ) ;
 cm -> interp_filter = read_interp_filter ( rb ) ;
 for ( i = 0 ;
 i < REFS_PER_FRAME ;
 ++ i ) {
 RefBuffer * const ref_buf = & cm -> frame_refs [ i ] ;
 vp9_setup_scale_factors_for_frame ( & ref_buf -> sf , ref_buf -> buf -> y_crop_width , ref_buf -> buf -> y_crop_height , cm -> width , cm -> height ) ;
 if ( vp9_is_scaled ( & ref_buf -> sf ) ) vp9_extend_frame_borders ( ref_buf -> buf ) ;
 }
 }
 }
 if ( ! cm -> error_resilient_mode ) {
 cm -> coding_use_prev_mi = 1 ;
 cm -> refresh_frame_context = vp9_rb_read_bit ( rb ) ;
 cm -> frame_parallel_decoding_mode = vp9_rb_read_bit ( rb ) ;
 }
 else {
 cm -> coding_use_prev_mi = 0 ;
 cm -> refresh_frame_context = 0 ;
 cm -> frame_parallel_decoding_mode = 1 ;
 }
 cm -> frame_context_idx = vp9_rb_read_literal ( rb , FRAME_CONTEXTS_LOG2 ) ;
 if ( frame_is_intra_only ( cm ) || cm -> error_resilient_mode ) vp9_setup_past_independence ( cm ) ;
 setup_loopfilter ( & cm -> lf , rb ) ;
 setup_quantization ( cm , & pbi -> mb , rb ) ;
 setup_segmentation ( & cm -> seg , rb ) ;
 setup_tile_info ( cm , rb ) ;
 sz = vp9_rb_read_literal ( rb , 16 ) ;
 if ( sz == 0 ) vpx_internal_error ( & cm -> error , VPX_CODEC_CORRUPT_FRAME , "Invalid header size" ) ;
 return sz ;
 }