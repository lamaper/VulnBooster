void vp9_lpf_vertical_8_dual_sse2 ( uint8_t * s , int p , const uint8_t * blimit0 , const uint8_t * limit0 , const uint8_t * thresh0 , const uint8_t * blimit1 , const uint8_t * limit1 , const uint8_t * thresh1 ) {
 DECLARE_ALIGNED_ARRAY ( 16 , unsigned char , t_dst , 16 * 8 ) ;
 unsigned char * src [ 2 ] ;
 unsigned char * dst [ 2 ] ;
 transpose8x16 ( s - 4 , s - 4 + p * 8 , p , t_dst , 16 ) ;
 vp9_lpf_horizontal_8_dual_sse2 ( t_dst + 4 * 16 , 16 , blimit0 , limit0 , thresh0 , blimit1 , limit1 , thresh1 ) ;
 src [ 0 ] = t_dst ;
 src [ 1 ] = t_dst + 8 ;
 dst [ 0 ] = s - 4 ;
 dst [ 1 ] = s - 4 + p * 8 ;
 transpose ( src , 16 , dst , p , 2 ) ;
 }