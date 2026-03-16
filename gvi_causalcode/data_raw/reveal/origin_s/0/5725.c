void vp9_convolve8_vert_c ( const uint8_t * src , ptrdiff_t src_stride , uint8_t * dst , ptrdiff_t dst_stride , const int16_t * filter_x , int x_step_q4 , const int16_t * filter_y , int y_step_q4 , int w , int h ) {
 const InterpKernel * const filters_y = get_filter_base ( filter_y ) ;
 const int y0_q4 = get_filter_offset ( filter_y , filters_y ) ;
 ( void ) filter_x ;
 ( void ) x_step_q4 ;
 convolve_vert ( src , src_stride , dst , dst_stride , filters_y , y0_q4 , y_step_q4 , w , h ) ;
 }