void vp9_idct16x16_10_add_c ( const tran_low_t * input , uint8_t * dest , int stride ) {
 tran_low_t out [ 16 * 16 ] = {
 0 }
 ;
 tran_low_t * outptr = out ;
 int i , j ;
 tran_low_t temp_in [ 16 ] , temp_out [ 16 ] ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 idct16 ( input , outptr ) ;
 input += 16 ;
 outptr += 16 ;
 }
 for ( i = 0 ;
 i < 16 ;
 ++ i ) {
 for ( j = 0 ;
 j < 16 ;
 ++ j ) temp_in [ j ] = out [ j * 16 + i ] ;
 idct16 ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 16 ;
 ++ j ) dest [ j * stride + i ] = clip_pixel ( ROUND_POWER_OF_TWO ( temp_out [ j ] , 6 ) + dest [ j * stride + i ] ) ;
 }
 }