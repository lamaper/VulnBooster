void vp9_fdct32x32_rd_c ( const int16_t * input , int16_t * out , int stride ) {
 int i , j ;
 int output [ 32 * 32 ] ;
 for ( i = 0 ;
 i < 32 ;
 ++ i ) {
 int temp_in [ 32 ] , temp_out [ 32 ] ;
 for ( j = 0 ;
 j < 32 ;
 ++ j ) temp_in [ j ] = input [ j * stride + i ] * 4 ;
 fdct32 ( temp_in , temp_out , 0 ) ;
 for ( j = 0 ;
 j < 32 ;
 ++ j ) output [ j * 32 + i ] = ( temp_out [ j ] + 1 + ( temp_out [ j ] > 0 ) ) >> 2 ;
 }
 for ( i = 0 ;
 i < 32 ;
 ++ i ) {
 int temp_in [ 32 ] , temp_out [ 32 ] ;
 for ( j = 0 ;
 j < 32 ;
 ++ j ) temp_in [ j ] = output [ j + i * 32 ] ;
 fdct32 ( temp_in , temp_out , 1 ) ;
 for ( j = 0 ;
 j < 32 ;
 ++ j ) out [ j + i * 32 ] = temp_out [ j ] ;
 }
 }