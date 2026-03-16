int vp8_yv12_alloc_frame_buffer ( YV12_BUFFER_CONFIG * ybf , int width , int height , int border ) {
 if ( ybf ) {
 vp8_yv12_de_alloc_frame_buffer ( ybf ) ;
 return vp8_yv12_realloc_frame_buffer ( ybf , width , height , border ) ;
 }
 return - 2 ;
 }