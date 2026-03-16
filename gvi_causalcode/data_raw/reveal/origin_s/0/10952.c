int vp8_yv12_realloc_frame_buffer ( YV12_BUFFER_CONFIG * ybf , int width , int height , int border ) {
 if ( ybf ) {
 int aligned_width = ( width + 15 ) & ~ 15 ;
 int aligned_height = ( height + 15 ) & ~ 15 ;
 int y_stride = ( ( aligned_width + 2 * border ) + 31 ) & ~ 31 ;
 int yplane_size = ( aligned_height + 2 * border ) * y_stride ;
 int uv_width = aligned_width >> 1 ;
 int uv_height = aligned_height >> 1 ;
 int uv_stride = y_stride >> 1 ;
 int uvplane_size = ( uv_height + border ) * uv_stride ;
 const int frame_size = yplane_size + 2 * uvplane_size ;
 if ( ! ybf -> buffer_alloc ) {
 ybf -> buffer_alloc = ( uint8_t * ) vpx_memalign ( 32 , frame_size ) ;
 ybf -> buffer_alloc_sz = frame_size ;
 }
 if ( ! ybf -> buffer_alloc || ybf -> buffer_alloc_sz < frame_size ) return - 1 ;
 if ( border & 0x1f ) return - 3 ;
 ybf -> y_crop_width = width ;
 ybf -> y_crop_height = height ;
 ybf -> y_width = aligned_width ;
 ybf -> y_height = aligned_height ;
 ybf -> y_stride = y_stride ;
 ybf -> uv_crop_width = ( width + 1 ) / 2 ;
 ybf -> uv_crop_height = ( height + 1 ) / 2 ;
 ybf -> uv_width = uv_width ;
 ybf -> uv_height = uv_height ;
 ybf -> uv_stride = uv_stride ;
 ybf -> alpha_width = 0 ;
 ybf -> alpha_height = 0 ;
 ybf -> alpha_stride = 0 ;
 ybf -> border = border ;
 ybf -> frame_size = frame_size ;
 ybf -> y_buffer = ybf -> buffer_alloc + ( border * y_stride ) + border ;
 ybf -> u_buffer = ybf -> buffer_alloc + yplane_size + ( border / 2 * uv_stride ) + border / 2 ;
 ybf -> v_buffer = ybf -> buffer_alloc + yplane_size + uvplane_size + ( border / 2 * uv_stride ) + border / 2 ;
 ybf -> alpha_buffer = NULL ;
 ybf -> corrupted = 0 ;
 return 0 ;
 }
 return - 2 ;
 }