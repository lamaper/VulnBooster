static void var_filter_block2d_bil_w8 ( const uint8_t * src_ptr , uint8_t * output_ptr , unsigned int src_pixels_per_line , int pixel_step , unsigned int output_height , unsigned int output_width , const uint16_t * vpx_filter ) {
 const uint8x8_t f0 = vmov_n_u8 ( ( uint8_t ) vpx_filter [ 0 ] ) ;
 const uint8x8_t f1 = vmov_n_u8 ( ( uint8_t ) vpx_filter [ 1 ] ) ;
 unsigned int i ;
 for ( i = 0 ;
 i < output_height ;
 ++ i ) {
 const uint8x8_t src_0 = vld1_u8 ( & src_ptr [ 0 ] ) ;
 const uint8x8_t src_1 = vld1_u8 ( & src_ptr [ pixel_step ] ) ;
 const uint16x8_t a = vmull_u8 ( src_0 , f0 ) ;
 const uint16x8_t b = vmlal_u8 ( a , src_1 , f1 ) ;
 const uint8x8_t out = vrshrn_n_u16 ( b , FILTER_BITS ) ;
 vst1_u8 ( & output_ptr [ 0 ] , out ) ;
 src_ptr += src_pixels_per_line ;
 output_ptr += output_width ;
 }
 }