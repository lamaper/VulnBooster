static void copy_frame ( YV12_BUFFER_CONFIG dest , const YV12_BUFFER_CONFIG src ) {
 int r ;
 const uint8_t * srcbuf = src . y_buffer ;
 uint8_t * destbuf = dest . y_buffer ;
 assert ( dest . y_width == src . y_width ) ;
 assert ( dest . y_height == src . y_height ) ;
 for ( r = 0 ;
 r < dest . y_height ;
 ++ r ) {
 vpx_memcpy ( destbuf , srcbuf , dest . y_width ) ;
 destbuf += dest . y_stride ;
 srcbuf += src . y_stride ;
 }
 }