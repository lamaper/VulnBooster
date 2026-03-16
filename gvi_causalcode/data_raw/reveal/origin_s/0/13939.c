void vp9_free_context_buffers ( VP9_COMMON * cm ) {
 free_mi ( cm ) ;
 vpx_free ( cm -> last_frame_seg_map ) ;
 cm -> last_frame_seg_map = NULL ;
 vpx_free ( cm -> above_context ) ;
 cm -> above_context = NULL ;
 vpx_free ( cm -> above_seg_context ) ;
 cm -> above_seg_context = NULL ;
 }