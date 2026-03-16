static void resize_context_buffers ( VP9_COMMON * cm , int width , int height ) {


 const int new_mi_rows = ALIGN_POWER_OF_TWO ( height , MI_SIZE_LOG2 ) >> MI_SIZE_LOG2 ;
 const int new_mi_cols = ALIGN_POWER_OF_TWO ( width , MI_SIZE_LOG2 ) >> MI_SIZE_LOG2 ;
 if ( new_mi_cols > cm -> mi_cols || new_mi_rows > cm -> mi_rows ) {
 if ( vp9_alloc_context_buffers ( cm , width , height ) ) vpx_internal_error ( & cm -> error , VPX_CODEC_MEM_ERROR , "Failed to allocate context buffers" ) ;
 }
 else {
 vp9_set_mb_mi ( cm , width , height ) ;
 }
 vp9_init_context_buffers ( cm ) ;
 cm -> width = width ;
 cm -> height = height ;
 }
 }