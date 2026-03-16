static unsigned int get_sby_perpixel_diff_variance ( VP9_COMP * cpi , const struct buf_2d * ref , int mi_row , int mi_col , BLOCK_SIZE bs ) {
 const YV12_BUFFER_CONFIG * last = get_ref_frame_buffer ( cpi , LAST_FRAME ) ;
 const uint8_t * last_y = & last -> y_buffer [ mi_row * MI_SIZE * last -> y_stride + mi_col * MI_SIZE ] ;
 unsigned int sse ;
 const unsigned int var = cpi -> fn_ptr [ bs ] . vf ( ref -> buf , ref -> stride , last_y , last -> y_stride , & sse ) ;
 return ROUND_POWER_OF_TWO ( var , num_pels_log2_lookup [ bs ] ) ;
 }