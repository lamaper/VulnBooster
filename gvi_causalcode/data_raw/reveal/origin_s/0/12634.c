void vp9_convolve_avg_c ( const uint8_t * src , ptrdiff_t src_stride , uint8_t * dst , ptrdiff_t dst_stride , const int16_t * filter_x , int filter_x_stride , const int16_t * filter_y , int filter_y_stride , int w , int h ) {
 int x , y ;
 ( void ) filter_x ;
 ( void ) filter_x_stride ;
 ( void ) filter_y ;
 ( void ) filter_y_stride ;
 for ( y = 0 ;
 y < h ;
 ++ y ) {
 for ( x = 0 ;
 x < w ;
 ++ x ) dst [ x ] = ROUND_POWER_OF_TWO ( dst [ x ] + src [ x ] , 1 ) ;
 src += src_stride ;
 dst += dst_stride ;
 }
 }