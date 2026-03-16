static void alloc_ref_frame_buffers ( VP9_COMP * cpi ) {
 VP9_COMMON * const cm = & cpi -> common ;
 if ( vp9_alloc_ref_frame_buffers ( cm , cm -> width , cm -> height ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_MEM_ERROR , "Failed to allocate frame buffers" ) ;
 }