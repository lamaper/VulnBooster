static void convolve ( const uint8_t * src , ptrdiff_t src_stride , uint8_t * dst , ptrdiff_t dst_stride , const InterpKernel * const x_filters , int x0_q4 , int x_step_q4 , const InterpKernel * const y_filters , int y0_q4 , int y_step_q4 , int w , int h ) {
 uint8_t temp [ 135 * 64 ] ;
 int intermediate_height = ( ( ( h - 1 ) * y_step_q4 + 15 ) >> 4 ) + SUBPEL_TAPS ;
 assert ( w <= 64 ) ;
 assert ( h <= 64 ) ;
 assert ( y_step_q4 <= 32 ) ;
 assert ( x_step_q4 <= 32 ) ;
 if ( intermediate_height < h ) intermediate_height = h ;
 convolve_horiz ( src - src_stride * ( SUBPEL_TAPS / 2 - 1 ) , src_stride , temp , 64 , x_filters , x0_q4 , x_step_q4 , w , intermediate_height ) ;
 convolve_vert ( temp + 64 * ( SUBPEL_TAPS / 2 - 1 ) , 64 , dst , dst_stride , y_filters , y0_q4 , y_step_q4 , w , h ) ;
 }