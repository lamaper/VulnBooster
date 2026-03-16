static void iadst4 ( const tran_low_t * input , tran_low_t * output ) {
 tran_high_t s0 , s1 , s2 , s3 , s4 , s5 , s6 , s7 ;
 tran_high_t x0 = input [ 0 ] ;
 tran_high_t x1 = input [ 1 ] ;
 tran_high_t x2 = input [ 2 ] ;
 tran_high_t x3 = input [ 3 ] ;
 if ( ! ( x0 | x1 | x2 | x3 ) ) {
 output [ 0 ] = output [ 1 ] = output [ 2 ] = output [ 3 ] = 0 ;
 return ;
 }
 s0 = sinpi_1_9 * x0 ;
 s1 = sinpi_2_9 * x0 ;
 s2 = sinpi_3_9 * x1 ;
 s3 = sinpi_4_9 * x2 ;
 s4 = sinpi_1_9 * x2 ;
 s5 = sinpi_2_9 * x3 ;
 s6 = sinpi_4_9 * x3 ;
 s7 = x0 - x2 + x3 ;
 x0 = s0 + s3 + s5 ;
 x1 = s1 - s4 - s6 ;
 x2 = sinpi_3_9 * s7 ;
 x3 = s2 ;
 s0 = x0 + x3 ;
 s1 = x1 + x3 ;
 s2 = x2 ;
 s3 = x0 + x1 - x3 ;
 output [ 0 ] = dct_const_round_shift ( s0 ) ;
 output [ 1 ] = dct_const_round_shift ( s1 ) ;
 output [ 2 ] = dct_const_round_shift ( s2 ) ;
 output [ 3 ] = dct_const_round_shift ( s3 ) ;
 }