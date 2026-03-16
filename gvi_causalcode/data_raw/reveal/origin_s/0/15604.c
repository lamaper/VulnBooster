static void var_filter_block2d_bil_second_pass ( const uint16_t * src_ptr , uint8_t * output_ptr , unsigned int src_pixels_per_line , unsigned int pixel_step , unsigned int output_height , unsigned int output_width , const int16_t * vp9_filter ) {
 unsigned int i , j ;
 for ( i = 0 ;
 i < output_height ;
 i ++ ) {
 for ( j = 0 ;
 j < output_width ;
 j ++ ) {
 output_ptr [ j ] = ROUND_POWER_OF_TWO ( ( int ) src_ptr [ 0 ] * vp9_filter [ 0 ] + ( int ) src_ptr [ pixel_step ] * vp9_filter [ 1 ] , FILTER_BITS ) ;
 src_ptr ++ ;
 }
 src_ptr += src_pixels_per_line - output_width ;
 output_ptr += output_width ;
 }
 }