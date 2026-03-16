void vp9_remove_common ( VP9_COMMON * cm ) {
 vp9_free_ref_frame_buffers ( cm ) ;
 vp9_free_context_buffers ( cm ) ;
 vp9_free_internal_frame_buffers ( & cm -> int_frame_buffers ) ;
 }