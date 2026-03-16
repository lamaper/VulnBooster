void vp9_iht4x4_16_add_c ( const tran_low_t * input , uint8_t * dest , int stride , int tx_type ) {
 const transform_2d IHT_4 [ ] = {
 {
 idct4 , idct4 }
 , {
 iadst4 , idct4 }
 , {
 idct4 , iadst4 }
 , {
 iadst4 , iadst4 }
 }
 ;
 int i , j ;
 tran_low_t out [ 4 * 4 ] ;
 tran_low_t * outptr = out ;
 tran_low_t temp_in [ 4 ] , temp_out [ 4 ] ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 IHT_4 [ tx_type ] . rows ( input , outptr ) ;
 input += 4 ;
 outptr += 4 ;
 }
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 for ( j = 0 ;
 j < 4 ;
 ++ j ) temp_in [ j ] = out [ j * 4 + i ] ;
 IHT_4 [ tx_type ] . cols ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 4 ;
 ++ j ) dest [ j * stride + i ] = clip_pixel ( ROUND_POWER_OF_TWO ( temp_out [ j ] , 4 ) + dest [ j * stride + i ] ) ;
 }
 }