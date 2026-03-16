void vp9_init_context_buffers ( VP9_COMMON * cm ) {
 setup_mi ( cm ) ;
 if ( cm -> last_frame_seg_map ) vpx_memset ( cm -> last_frame_seg_map , 0 , cm -> mi_rows * cm -> mi_cols ) ;
 }