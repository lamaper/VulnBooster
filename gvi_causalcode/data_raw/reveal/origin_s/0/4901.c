static void convolve_vert ( const uint8_t * src , ptrdiff_t src_stride , uint8_t * dst , ptrdiff_t dst_stride , const InterpKernel * y_filters , int y0_q4 , int y_step_q4 , int w , int h ) {
 int x , y ;
 src -= src_stride * ( SUBPEL_TAPS / 2 - 1 ) ;
 for ( x = 0 ;
 x < w ;
 ++ x ) {
 int y_q4 = y0_q4 ;
 for ( y = 0 ;
 y < h ;
 ++ y ) {
 const unsigned char * src_y = & src [ ( y_q4 >> SUBPEL_BITS ) * src_stride ] ;
 const int16_t * const y_filter = y_filters [ y_q4 & SUBPEL_MASK ] ;
 int k , sum = 0 ;
 for ( k = 0 ;
 k < SUBPEL_TAPS ;
 ++ k ) sum += src_y [ k * src_stride ] * y_filter [ k ] ;
 dst [ y * dst_stride ] = clip_pixel ( ROUND_POWER_OF_TWO ( sum , FILTER_BITS ) ) ;
 y_q4 += y_step_q4 ;
 }
 ++ src ;
 ++ dst ;
 }
 }