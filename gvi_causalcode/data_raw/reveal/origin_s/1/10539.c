void vp9_fht16x16_c ( const int16_t * input , int16_t * output , int stride , int tx_type ) {
 if ( tx_type == DCT_DCT ) {
 vp9_fdct16x16_c ( input , output , stride ) ;
 }
 else {
 int16_t out [ 256 ] ;
 int16_t * outptr = & out [ 0 ] ;
 int i , j ;
 int16_t temp_in [ 16 ] , temp_out [ 16 ] ;
 const transform_2d ht = FHT_16 [ tx_type ] ;
 for ( i = 0 ;
 i < 16 ;
 ++ i ) {
 for ( j = 0 ;
 j < 16 ;
 ++ j ) temp_in [ j ] = input [ j * stride + i ] * 4 ;
 ht . cols ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 16 ;
 ++ j ) outptr [ j * 16 + i ] = ( temp_out [ j ] + 1 + ( temp_out [ j ] < 0 ) ) >> 2 ;
 }
 for ( i = 0 ;
 i < 16 ;
 ++ i ) {
 for ( j = 0 ;
 j < 16 ;
 ++ j ) temp_in [ j ] = out [ j + i * 16 ] ;
 ht . rows ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 16 ;
 ++ j ) output [ j + i * 16 ] = temp_out [ j ] ;
 }
 }
 }