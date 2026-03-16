void vp9_setup_scale_factors_for_frame ( struct scale_factors * sf , int other_w , int other_h , int this_w , int this_h ) {
 if ( ! valid_ref_frame_size ( other_w , other_h , this_w , this_h ) ) {
 sf -> x_scale_fp = REF_INVALID_SCALE ;
 sf -> y_scale_fp = REF_INVALID_SCALE ;
 return ;
 }
 sf -> x_scale_fp = get_fixed_point_scale_factor ( other_w , this_w ) ;
 sf -> y_scale_fp = get_fixed_point_scale_factor ( other_h , this_h ) ;
 sf -> x_step_q4 = scaled_x ( 16 , sf ) ;
 sf -> y_step_q4 = scaled_y ( 16 , sf ) ;
 if ( vp9_is_scaled ( sf ) ) {
 sf -> scale_value_x = scaled_x ;
 sf -> scale_value_y = scaled_y ;
 }
 else {
 sf -> scale_value_x = unscaled_value ;
 sf -> scale_value_y = unscaled_value ;
 }
 if ( sf -> x_step_q4 == 16 ) {
 if ( sf -> y_step_q4 == 16 ) {
 sf -> predict [ 0 ] [ 0 ] [ 0 ] = vp9_convolve_copy ;
 sf -> predict [ 0 ] [ 0 ] [ 1 ] = vp9_convolve_avg ;
 sf -> predict [ 0 ] [ 1 ] [ 0 ] = vp9_convolve8_vert ;
 sf -> predict [ 0 ] [ 1 ] [ 1 ] = vp9_convolve8_avg_vert ;
 sf -> predict [ 1 ] [ 0 ] [ 0 ] = vp9_convolve8_horiz ;
 sf -> predict [ 1 ] [ 0 ] [ 1 ] = vp9_convolve8_avg_horiz ;
 }
 else {
 sf -> predict [ 0 ] [ 0 ] [ 0 ] = vp9_convolve8_vert ;
 sf -> predict [ 0 ] [ 0 ] [ 1 ] = vp9_convolve8_avg_vert ;
 sf -> predict [ 0 ] [ 1 ] [ 0 ] = vp9_convolve8_vert ;
 sf -> predict [ 0 ] [ 1 ] [ 1 ] = vp9_convolve8_avg_vert ;
 sf -> predict [ 1 ] [ 0 ] [ 0 ] = vp9_convolve8 ;
 sf -> predict [ 1 ] [ 0 ] [ 1 ] = vp9_convolve8_avg ;
 }
 }
 else {
 if ( sf -> y_step_q4 == 16 ) {
 sf -> predict [ 0 ] [ 0 ] [ 0 ] = vp9_convolve8_horiz ;
 sf -> predict [ 0 ] [ 0 ] [ 1 ] = vp9_convolve8_avg_horiz ;
 sf -> predict [ 0 ] [ 1 ] [ 0 ] = vp9_convolve8 ;
 sf -> predict [ 0 ] [ 1 ] [ 1 ] = vp9_convolve8_avg ;
 sf -> predict [ 1 ] [ 0 ] [ 0 ] = vp9_convolve8_horiz ;
 sf -> predict [ 1 ] [ 0 ] [ 1 ] = vp9_convolve8_avg_horiz ;
 }
 else {
 sf -> predict [ 0 ] [ 0 ] [ 0 ] = vp9_convolve8 ;
 sf -> predict [ 0 ] [ 0 ] [ 1 ] = vp9_convolve8_avg ;
 sf -> predict [ 0 ] [ 1 ] [ 0 ] = vp9_convolve8 ;
 sf -> predict [ 0 ] [ 1 ] [ 1 ] = vp9_convolve8_avg ;
 sf -> predict [ 1 ] [ 0 ] [ 0 ] = vp9_convolve8 ;
 sf -> predict [ 1 ] [ 0 ] [ 1 ] = vp9_convolve8_avg ;
 }
 }
 sf -> predict [ 1 ] [ 1 ] [ 0 ] = vp9_convolve8 ;
 sf -> predict [ 1 ] [ 1 ] [ 1 ] = vp9_convolve8_avg ;
 }