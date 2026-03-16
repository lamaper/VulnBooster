void vp9_convolve8_avg_c ( const uint8_t * src , ptrdiff_t src_stride , uint8_t * dst , ptrdiff_t dst_stride , const int16_t * filter_x , int x_step_q4 , const int16_t * filter_y , int y_step_q4 , int w , int h ) {
 DECLARE_ALIGNED_ARRAY ( 16 , uint8_t , temp , 64 * 64 ) ;
 assert ( w <= 64 ) ;
 assert ( h <= 64 ) ;
 vp9_convolve8_c ( src , src_stride , temp , 64 , filter_x , x_step_q4 , filter_y , y_step_q4 , w , h ) ;
 vp9_convolve_avg_c ( temp , 64 , dst , dst_stride , NULL , 0 , NULL , 0 , w , h ) ;
 }