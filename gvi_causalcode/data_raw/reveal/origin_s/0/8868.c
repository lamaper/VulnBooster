static void convolve_avg_horiz ( const uint8_t * src , ptrdiff_t src_stride , uint8_t * dst , ptrdiff_t dst_stride , const InterpKernel * x_filters , int x0_q4 , int x_step_q4 , int w , int h ) {
 int x , y ;
 src -= SUBPEL_TAPS / 2 - 1 ;
 for ( y = 0 ;
 y < h ;
 ++ y ) {
 int x_q4 = x0_q4 ;
 for ( x = 0 ;
 x < w ;
 ++ x ) {
 const uint8_t * const src_x = & src [ x_q4 >> SUBPEL_BITS ] ;
 const int16_t * const x_filter = x_filters [ x_q4 & SUBPEL_MASK ] ;
 int k , sum = 0 ;
 for ( k = 0 ;
 k < SUBPEL_TAPS ;
 ++ k ) sum += src_x [ k ] * x_filter [ k ] ;
 dst [ x ] = ROUND_POWER_OF_TWO ( dst [ x ] + clip_pixel ( ROUND_POWER_OF_TWO ( sum , FILTER_BITS ) ) , 1 ) ;
 x_q4 += x_step_q4 ;
 }
 src += src_stride ;
 dst += dst_stride ;
 }
 }