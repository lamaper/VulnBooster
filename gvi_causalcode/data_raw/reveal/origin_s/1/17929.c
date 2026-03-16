void vp9_fdct4x4_c ( const int16_t * input , int16_t * output , int stride ) {
 int pass ;
 int16_t intermediate [ 4 * 4 ] ;
 const int16_t * in = input ;
 int16_t * out = intermediate ;
 for ( pass = 0 ;
 pass < 2 ;
 ++ pass ) {
 int input [ 4 ] ;
 int step [ 4 ] ;
 int temp1 , temp2 ;
 int i ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 if ( 0 == pass ) {
 input [ 0 ] = in [ 0 * stride ] * 16 ;
 input [ 1 ] = in [ 1 * stride ] * 16 ;
 input [ 2 ] = in [ 2 * stride ] * 16 ;
 input [ 3 ] = in [ 3 * stride ] * 16 ;
 if ( i == 0 && input [ 0 ] ) {
 input [ 0 ] += 1 ;
 }
 }
 else {
 input [ 0 ] = in [ 0 * 4 ] ;
 input [ 1 ] = in [ 1 * 4 ] ;
 input [ 2 ] = in [ 2 * 4 ] ;
 input [ 3 ] = in [ 3 * 4 ] ;
 }
 step [ 0 ] = input [ 0 ] + input [ 3 ] ;
 step [ 1 ] = input [ 1 ] + input [ 2 ] ;
 step [ 2 ] = input [ 1 ] - input [ 2 ] ;
 step [ 3 ] = input [ 0 ] - input [ 3 ] ;
 temp1 = ( step [ 0 ] + step [ 1 ] ) * cospi_16_64 ;
 temp2 = ( step [ 0 ] - step [ 1 ] ) * cospi_16_64 ;
 out [ 0 ] = fdct_round_shift ( temp1 ) ;
 out [ 2 ] = fdct_round_shift ( temp2 ) ;
 temp1 = step [ 2 ] * cospi_24_64 + step [ 3 ] * cospi_8_64 ;
 temp2 = - step [ 2 ] * cospi_8_64 + step [ 3 ] * cospi_24_64 ;
 out [ 1 ] = fdct_round_shift ( temp1 ) ;
 out [ 3 ] = fdct_round_shift ( temp2 ) ;
 in ++ ;
 out += 4 ;
 }
 in = intermediate ;
 out = output ;
 }
 {
 int i , j ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 for ( j = 0 ;
 j < 4 ;
 ++ j ) output [ j + i * 4 ] = ( output [ j + i * 4 ] + 1 ) >> 2 ;
 }
 }
 }