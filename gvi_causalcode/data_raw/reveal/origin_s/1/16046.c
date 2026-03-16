void vp9_lpf_vertical_16_sse2 ( unsigned char * s , int p , const unsigned char * blimit , const unsigned char * limit , const unsigned char * thresh ) {
 DECLARE_ALIGNED_ARRAY ( 8 , unsigned char , t_dst , 8 * 16 ) ;
 unsigned char * src [ 2 ] ;
 unsigned char * dst [ 2 ] ;
 src [ 0 ] = s - 8 ;
 src [ 1 ] = s ;
 dst [ 0 ] = t_dst ;
 dst [ 1 ] = t_dst + 8 * 8 ;
 transpose ( src , p , dst , 8 , 2 ) ;
 mb_lpf_horizontal_edge_w_sse2_8 ( t_dst + 8 * 8 , 8 , blimit , limit , thresh ) ;
 src [ 0 ] = t_dst ;
 src [ 1 ] = t_dst + 8 * 8 ;
 dst [ 0 ] = s - 8 ;
 dst [ 1 ] = s ;
 transpose ( src , 8 , dst , p , 2 ) ;
 }