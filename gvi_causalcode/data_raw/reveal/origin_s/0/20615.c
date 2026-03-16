void vp9_convolve_copy_c ( const uint8_t * src , ptrdiff_t src_stride , uint8_t * dst , ptrdiff_t dst_stride , const int16_t * filter_x , int filter_x_stride , const int16_t * filter_y , int filter_y_stride , int w , int h ) {
 int r ;
 ( void ) filter_x ;
 ( void ) filter_x_stride ;
 ( void ) filter_y ;
 ( void ) filter_y_stride ;
 for ( r = h ;
 r > 0 ;
 -- r ) {
 vpx_memcpy ( dst , src , w ) ;
 src += src_stride ;
 dst += dst_stride ;
 }
 }