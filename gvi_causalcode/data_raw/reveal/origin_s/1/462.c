void vp9_iht16x16_256_add_c ( const int16_t * input , uint8_t * dest , int stride , int tx_type ) {
 int i , j ;
 int16_t out [ 16 * 16 ] ;
 int16_t * outptr = out ;
 int16_t temp_in [ 16 ] , temp_out [ 16 ] ;
 const transform_2d ht = IHT_16 [ tx_type ] ;
 for ( i = 0 ;
 i < 16 ;
 ++ i ) {
 ht . rows ( input , outptr ) ;
 input += 16 ;
 outptr += 16 ;
 }
 for ( i = 0 ;
 i < 16 ;
 ++ i ) {
 for ( j = 0 ;
 j < 16 ;
 ++ j ) temp_in [ j ] = out [ j * 16 + i ] ;
 ht . cols ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 16 ;
 ++ j ) dest [ j * stride + i ] = clip_pixel ( ROUND_POWER_OF_TWO ( temp_out [ j ] , 6 ) + dest [ j * stride + i ] ) ;
 }
 }