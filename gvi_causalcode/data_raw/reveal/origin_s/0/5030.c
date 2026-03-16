void reference_8x8_dct_2d ( const int16_t input [ kNumCoeffs ] , double output [ kNumCoeffs ] ) {
 for ( int i = 0 ;
 i < 8 ;
 ++ i ) {
 double temp_in [ 8 ] , temp_out [ 8 ] ;
 for ( int j = 0 ;
 j < 8 ;
 ++ j ) temp_in [ j ] = input [ j * 8 + i ] ;
 reference_8x8_dct_1d ( temp_in , temp_out , 1 ) ;
 for ( int j = 0 ;
 j < 8 ;
 ++ j ) output [ j * 8 + i ] = temp_out [ j ] ;
 }
 for ( int i = 0 ;
 i < 8 ;
 ++ i ) {
 double temp_in [ 8 ] , temp_out [ 8 ] ;
 for ( int j = 0 ;
 j < 8 ;
 ++ j ) temp_in [ j ] = output [ j + i * 8 ] ;
 reference_8x8_dct_1d ( temp_in , temp_out , 1 ) ;
 for ( int j = 0 ;
 j < 8 ;
 ++ j ) output [ j + i * 8 ] = temp_out [ j ] * 2 ;
 }
 }