static void idct4 ( const int16_t * input , int16_t * output ) {
 int16_t step [ 4 ] ;
 int temp1 , temp2 ;
 temp1 = ( input [ 0 ] + input [ 2 ] ) * cospi_16_64 ;
 temp2 = ( input [ 0 ] - input [ 2 ] ) * cospi_16_64 ;
 step [ 0 ] = dct_const_round_shift ( temp1 ) ;
 step [ 1 ] = dct_const_round_shift ( temp2 ) ;
 temp1 = input [ 1 ] * cospi_24_64 - input [ 3 ] * cospi_8_64 ;
 temp2 = input [ 1 ] * cospi_8_64 + input [ 3 ] * cospi_24_64 ;
 step [ 2 ] = dct_const_round_shift ( temp1 ) ;
 step [ 3 ] = dct_const_round_shift ( temp2 ) ;
 output [ 0 ] = step [ 0 ] + step [ 3 ] ;
 output [ 1 ] = step [ 1 ] + step [ 2 ] ;
 output [ 2 ] = step [ 1 ] - step [ 2 ] ;
 output [ 3 ] = step [ 0 ] - step [ 3 ] ;
 }