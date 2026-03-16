void vp9_idct32x32_34_add_c ( const int16_t * input , uint8_t * dest , int stride ) {
 int16_t out [ 32 * 32 ] = {
 0 }
 ;
 int16_t * outptr = out ;
 int i , j ;
 int16_t temp_in [ 32 ] , temp_out [ 32 ] ;
 for ( i = 0 ;
 i < 8 ;
 ++ i ) {
 idct32 ( input , outptr ) ;
 input += 32 ;
 outptr += 32 ;
 }
 for ( i = 0 ;
 i < 32 ;
 ++ i ) {
 for ( j = 0 ;
 j < 32 ;
 ++ j ) temp_in [ j ] = out [ j * 32 + i ] ;
 idct32 ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 32 ;
 ++ j ) dest [ j * stride + i ] = clip_pixel ( ROUND_POWER_OF_TWO ( temp_out [ j ] , 6 ) + dest [ j * stride + i ] ) ;
 }
 }