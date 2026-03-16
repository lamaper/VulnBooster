static void fadst4 ( const int16_t * input , int16_t * output ) {
 int x0 , x1 , x2 , x3 ;
 int s0 , s1 , s2 , s3 , s4 , s5 , s6 , s7 ;
 x0 = input [ 0 ] ;
 x1 = input [ 1 ] ;
 x2 = input [ 2 ] ;
 x3 = input [ 3 ] ;
 if ( ! ( x0 | x1 | x2 | x3 ) ) {
 output [ 0 ] = output [ 1 ] = output [ 2 ] = output [ 3 ] = 0 ;
 return ;
 }
 s0 = sinpi_1_9 * x0 ;
 s1 = sinpi_4_9 * x0 ;
 s2 = sinpi_2_9 * x1 ;
 s3 = sinpi_1_9 * x1 ;
 s4 = sinpi_3_9 * x2 ;
 s5 = sinpi_4_9 * x3 ;
 s6 = sinpi_2_9 * x3 ;
 s7 = x0 + x1 - x3 ;
 x0 = s0 + s2 + s5 ;
 x1 = sinpi_3_9 * s7 ;
 x2 = s1 - s3 + s6 ;
 x3 = s4 ;
 s0 = x0 + x3 ;
 s1 = x1 ;
 s2 = x2 - x3 ;
 s3 = x2 - x0 + x3 ;
 output [ 0 ] = fdct_round_shift ( s0 ) ;
 output [ 1 ] = fdct_round_shift ( s1 ) ;
 output [ 2 ] = fdct_round_shift ( s2 ) ;
 output [ 3 ] = fdct_round_shift ( s3 ) ;
 }