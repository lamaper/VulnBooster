void vp9_temporal_filter_apply_c ( uint8_t * frame1 , unsigned int stride , uint8_t * frame2 , unsigned int block_width , unsigned int block_height , int strength , int filter_weight , unsigned int * accumulator , uint16_t * count ) {
 unsigned int i , j , k ;
 int modifier ;
 int byte = 0 ;
 const int rounding = strength > 0 ? 1 << ( strength - 1 ) : 0 ;
 for ( i = 0 , k = 0 ;
 i < block_height ;
 i ++ ) {
 for ( j = 0 ;
 j < block_width ;
 j ++ , k ++ ) {
 int src_byte = frame1 [ byte ] ;
 int pixel_value = * frame2 ++ ;
 modifier = src_byte - pixel_value ;
 modifier *= modifier ;
 modifier *= 3 ;
 modifier += rounding ;
 modifier >>= strength ;
 if ( modifier > 16 ) modifier = 16 ;
 modifier = 16 - modifier ;
 modifier *= filter_weight ;
 count [ k ] += modifier ;
 accumulator [ k ] += modifier * pixel_value ;
 byte ++ ;
 }
 byte += stride - block_width ;
 }
 }