void vp9_idct8x8_12_add_c ( const tran_low_t * input , uint8_t * dest , int stride ) {
 tran_low_t out [ 8 * 8 ] = {
 0 }
 ;
 tran_low_t * outptr = out ;
 int i , j ;
 tran_low_t temp_in [ 8 ] , temp_out [ 8 ] ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 idct8 ( input , outptr ) ;
 input += 8 ;
 outptr += 8 ;
 }
 for ( i = 0 ;
 i < 8 ;
 ++ i ) {
 for ( j = 0 ;
 j < 8 ;
 ++ j ) temp_in [ j ] = out [ j * 8 + i ] ;
 idct8 ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 8 ;
 ++ j ) dest [ j * stride + i ] = clip_pixel ( ROUND_POWER_OF_TWO ( temp_out [ j ] , 5 ) + dest [ j * stride + i ] ) ;
 }
 }