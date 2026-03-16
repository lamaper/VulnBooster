void vp9_lpf_vertical_16_dual_sse2 ( unsigned char * s , int p , const uint8_t * blimit , const uint8_t * limit , const uint8_t * thresh ) {
 DECLARE_ALIGNED_ARRAY ( 16 , unsigned char , t_dst , 256 ) ;
 transpose8x16 ( s - 8 , s - 8 + 8 * p , p , t_dst , 16 ) ;
 transpose8x16 ( s , s + 8 * p , p , t_dst + 8 * 16 , 16 ) ;
 mb_lpf_horizontal_edge_w_sse2_16 ( t_dst + 8 * 16 , 16 , blimit , limit , thresh ) ;
 transpose8x16 ( t_dst , t_dst + 8 * 16 , 16 , s - 8 , p ) ;
 transpose8x16 ( t_dst + 8 , t_dst + 8 + 8 * 16 , 16 , s - 8 + 8 * p , p ) ;
 }