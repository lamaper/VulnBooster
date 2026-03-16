void vp9_fht4x4_c ( const int16_t * input , tran_low_t * output , int stride , int tx_type ) {
 if ( tx_type == DCT_DCT ) {
 vp9_fdct4x4_c ( input , output , stride ) ;
 }
 else {
 tran_low_t out [ 4 * 4 ] ;
 tran_low_t * outptr = & out [ 0 ] ;
 int i , j ;
 tran_low_t temp_in [ 4 ] , temp_out [ 4 ] ;
 const transform_2d ht = FHT_4 [ tx_type ] ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 for ( j = 0 ;
 j < 4 ;
 ++ j ) temp_in [ j ] = input [ j * stride + i ] * 16 ;
 if ( i == 0 && temp_in [ 0 ] ) temp_in [ 0 ] += 1 ;
 ht . cols ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 4 ;
 ++ j ) outptr [ j * 4 + i ] = temp_out [ j ] ;
 }
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 for ( j = 0 ;
 j < 4 ;
 ++ j ) temp_in [ j ] = out [ j + i * 4 ] ;
 ht . rows ( temp_in , temp_out ) ;
 for ( j = 0 ;
 j < 4 ;
 ++ j ) output [ j + i * 4 ] = ( temp_out [ j ] + 1 ) >> 2 ;
 }
 }
 }