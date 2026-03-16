static void update_frame_size ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 MACROBLOCKD * const xd = & cpi -> mb . e_mbd ;
 vp9_set_mb_mi ( cm , cm -> width , cm -> height ) ;
 vp9_init_context_buffers ( cm ) ;
 init_macroblockd ( cm , xd ) ;
 if ( is_two_pass_svc ( cpi ) ) {
 if ( vp9_realloc_frame_buffer ( & cpi -> alt_ref_buffer , cm -> width , cm -> height , cm -> subsampling_x , cm -> subsampling_y , # if CONFIG_VP9_HIGHBITDEPTH cm -> use_highbitdepth , # endif VP9_ENC_BORDER_IN_PIXELS , NULL , NULL , NULL ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_MEM_ERROR , "Failed to reallocate alt_ref_buffer" ) ;
 }
 }