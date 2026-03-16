int vp8_yv12_de_alloc_frame_buffer ( YV12_BUFFER_CONFIG * ybf ) {
 if ( ybf ) {
 if ( ybf -> buffer_alloc_sz > 0 ) {
 vpx_free ( ybf -> buffer_alloc ) ;
 }
 vpx_memset ( ybf , 0 , sizeof ( YV12_BUFFER_CONFIG ) ) ;
 }
 else {
 return - 1 ;
 }
 return 0 ;
 }