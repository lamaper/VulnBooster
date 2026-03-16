void vp9_lpf_vertical_8_sse2 ( unsigned char * s , int p , const unsigned char * blimit , const unsigned char * limit , const unsigned char * thresh , int count ) {
 DECLARE_ALIGNED_ARRAY ( 8 , unsigned char , t_dst , 8 * 8 ) ;
 unsigned char * src [ 1 ] ;
 unsigned char * dst [ 1 ] ;
 ( void ) count ;
 src [ 0 ] = s - 4 ;
 dst [ 0 ] = t_dst ;
 transpose ( src , p , dst , 8 , 1 ) ;
 vp9_lpf_horizontal_8_sse2 ( t_dst + 4 * 8 , 8 , blimit , limit , thresh , 1 ) ;
 src [ 0 ] = t_dst ;
 dst [ 0 ] = s - 4 ;
 transpose ( src , 8 , dst , p , 1 ) ;
 }