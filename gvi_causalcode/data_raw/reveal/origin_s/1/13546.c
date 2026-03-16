static void fdct4 ( const int16_t * input , int16_t * output ) {
 int16_t step [ 4 ] ;
 int temp1 , temp2 ;
 step [ 0 ] = input [ 0 ] + input [ 3 ] ;
 step [ 1 ] = input [ 1 ] + input [ 2 ] ;
 step [ 2 ] = input [ 1 ] - input [ 2 ] ;
 step [ 3 ] = input [ 0 ] - input [ 3 ] ;
 temp1 = ( step [ 0 ] + step [ 1 ] ) * cospi_16_64 ;
 temp2 = ( step [ 0 ] - step [ 1 ] ) * cospi_16_64 ;
 output [ 0 ] = fdct_round_shift ( temp1 ) ;
 output [ 2 ] = fdct_round_shift ( temp2 ) ;
 temp1 = step [ 2 ] * cospi_24_64 + step [ 3 ] * cospi_8_64 ;
 temp2 = - step [ 2 ] * cospi_8_64 + step [ 3 ] * cospi_24_64 ;
 output [ 1 ] = fdct_round_shift ( temp1 ) ;
 output [ 3 ] = fdct_round_shift ( temp2 ) ;
 }