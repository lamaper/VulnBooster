void vp9_idct32x32_1024_add_c ( const int16_t * input , uint8_t * dest , int stride ) {
 int16_t out [ 32 * 32 ] ;
 int16_t * outptr = out ;
 int i , j ;
 int16_t temp_in [ 32 ] , temp_out [ 32 ] ;
 for ( i = 0 ;
 i < 32 ;
 ++ i ) {
 int16_t zero_coeff [ 16 ] ;
 for ( j = 0 ;
 j < 16 ;
 ++ j ) zero_coeff [ j ] = input [ 2 * j ] | input [ 2 * j + 1 ] ;
 for ( j = 0 ;
 j < 8 ;
 ++ j ) zero_coeff [ j ] = zero_coeff [ 2 * j ] | zero_coeff [ 2 * j + 1 ] ;
 for ( j = 0 ;
 j < 4 ;
 ++ j ) zero_coeff [ j ] = zero_coeff [ 2 * j ] | zero_coeff [ 2 * j + 1 ] ;
 for ( j = 0 ;
 j < 2 ;
 ++ j ) zero_coeff [ j ] = zero_coeff [ 2 * j ] | zero_coeff [ 2 * j + 1 ] ;
 if ( zero_coeff [ 0 ] | zero_coeff [ 1 ] ) idct32 ( input , outptr ) ;
 else vpx_memset ( outptr , 0 , sizeof ( int16_t ) * 32 ) ;
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