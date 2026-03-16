unsigned int vp8_sub_pixel_variance8x8_neon ( const unsigned char * src , int src_stride , int xoffset , int yoffset , const unsigned char * dst , int dst_stride , unsigned int * sse ) {
 DECLARE_ALIGNED_ARRAY ( kAlign16 , uint8_t , temp2 , kHeight8 * kWidth8 ) ;
 DECLARE_ALIGNED_ARRAY ( kAlign16 , uint8_t , fdata3 , kHeight8PlusOne * kWidth8 ) ;
 if ( xoffset == 0 ) {
 var_filter_block2d_bil_w8 ( src , temp2 , src_stride , kWidth8 , kHeight8 , kWidth8 , bilinear_taps_coeff [ yoffset ] ) ;
 }
 else if ( yoffset == 0 ) {
 var_filter_block2d_bil_w8 ( src , temp2 , src_stride , kPixelStepOne , kHeight8PlusOne , kWidth8 , bilinear_taps_coeff [ xoffset ] ) ;
 }
 else {
 var_filter_block2d_bil_w8 ( src , fdata3 , src_stride , kPixelStepOne , kHeight8PlusOne , kWidth8 , bilinear_taps_coeff [ xoffset ] ) ;
 var_filter_block2d_bil_w8 ( fdata3 , temp2 , kWidth8 , kWidth8 , kHeight8 , kWidth8 , bilinear_taps_coeff [ yoffset ] ) ;
 }
 return variance8x8_neon ( temp2 , kWidth8 , dst , dst_stride , sse ) ;
 }