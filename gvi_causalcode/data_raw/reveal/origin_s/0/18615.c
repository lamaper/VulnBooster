int vp9_alloc_context_buffers ( VP9_COMMON * cm , int width , int height ) {
 vp9_free_context_buffers ( cm ) ;
 vp9_set_mb_mi ( cm , width , height ) ;
 if ( alloc_mi ( cm , cm -> mi_stride * calc_mi_size ( cm -> mi_rows ) ) ) goto fail ;
 cm -> last_frame_seg_map = ( uint8_t * ) vpx_calloc ( cm -> mi_rows * cm -> mi_cols , 1 ) ;
 if ( ! cm -> last_frame_seg_map ) goto fail ;
 cm -> above_context = ( ENTROPY_CONTEXT * ) vpx_calloc ( * mi_cols_aligned_to_sb ( cm -> mi_cols ) * MAX_MB_PLANE , sizeof ( * cm -> above_context ) ) ;
 if ( ! cm -> above_context ) goto fail ;
 cm -> above_seg_context = ( PARTITION_CONTEXT * ) vpx_calloc ( mi_cols_aligned_to_sb ( cm -> mi_cols ) , sizeof ( * cm -> above_seg_context ) ) ;
 if ( ! cm -> above_seg_context ) goto fail ;
 return 0 ;
 fail : vp9_free_context_buffers ( cm ) ;
 return 1 ;
 }