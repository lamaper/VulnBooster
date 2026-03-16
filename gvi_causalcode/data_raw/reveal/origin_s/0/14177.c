void vp9_update_reference_frames ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 if ( cm -> frame_type == KEY_FRAME ) {
 ref_cnt_fb ( cm -> frame_bufs , & cm -> ref_frame_map [ cpi -> gld_fb_idx ] , cm -> new_fb_idx ) ;
 ref_cnt_fb ( cm -> frame_bufs , & cm -> ref_frame_map [ cpi -> alt_fb_idx ] , cm -> new_fb_idx ) ;
 }
 else if ( vp9_preserve_existing_gf ( cpi ) ) {
 int tmp ;
 ref_cnt_fb ( cm -> frame_bufs , & cm -> ref_frame_map [ cpi -> alt_fb_idx ] , cm -> new_fb_idx ) ;
 tmp = cpi -> alt_fb_idx ;
 cpi -> alt_fb_idx = cpi -> gld_fb_idx ;
 cpi -> gld_fb_idx = tmp ;
 if ( is_two_pass_svc ( cpi ) ) {
 cpi -> svc . layer_context [ 0 ] . gold_ref_idx = cpi -> gld_fb_idx ;
 cpi -> svc . layer_context [ 0 ] . alt_ref_idx = cpi -> alt_fb_idx ;
 }
 }
 else {
 if ( cpi -> refresh_alt_ref_frame ) {
 int arf_idx = cpi -> alt_fb_idx ;
 if ( ( cpi -> oxcf . pass == 2 ) && cpi -> multi_arf_allowed ) {
 const GF_GROUP * const gf_group = & cpi -> twopass . gf_group ;
 arf_idx = gf_group -> arf_update_idx [ gf_group -> index ] ;
 }
 ref_cnt_fb ( cm -> frame_bufs , & cm -> ref_frame_map [ arf_idx ] , cm -> new_fb_idx ) ;
 vpx_memcpy ( cpi -> interp_filter_selected [ ALTREF_FRAME ] , cpi -> interp_filter_selected [ 0 ] , sizeof ( cpi -> interp_filter_selected [ 0 ] ) ) ;
 }
 if ( cpi -> refresh_golden_frame ) {
 ref_cnt_fb ( cm -> frame_bufs , & cm -> ref_frame_map [ cpi -> gld_fb_idx ] , cm -> new_fb_idx ) ;
 if ( ! cpi -> rc . is_src_frame_alt_ref ) vpx_memcpy ( cpi -> interp_filter_selected [ GOLDEN_FRAME ] , cpi -> interp_filter_selected [ 0 ] , sizeof ( cpi -> interp_filter_selected [ 0 ] ) ) ;
 else vpx_memcpy ( cpi -> interp_filter_selected [ GOLDEN_FRAME ] , cpi -> interp_filter_selected [ ALTREF_FRAME ] , sizeof ( cpi -> interp_filter_selected [ ALTREF_FRAME ] ) ) ;
 }
 }
 if ( cpi -> refresh_last_frame ) {
 ref_cnt_fb ( cm -> frame_bufs , & cm -> ref_frame_map [ cpi -> lst_fb_idx ] , cm -> new_fb_idx ) ;
 if ( ! cpi -> rc . is_src_frame_alt_ref ) vpx_memcpy ( cpi -> interp_filter_selected [ LAST_FRAME ] , cpi -> interp_filter_selected [ 0 ] , sizeof ( cpi -> interp_filter_selected [ 0 ] ) ) ;
 }

 vp9_denoiser_update_frame_info ( & cpi -> denoiser , * cpi -> Source , cpi -> common . frame_type , cpi -> refresh_alt_ref_frame , cpi -> refresh_golden_frame , cpi -> refresh_last_frame ) ;
 }
