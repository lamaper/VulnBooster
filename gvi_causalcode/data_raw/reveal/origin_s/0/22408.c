void vp9_fdct8x8_c ( const int16_t * input , tran_low_t * final_output , int stride ) {
 int i , j ;
 tran_low_t intermediate [ 64 ] ;
 {
 tran_low_t * output = intermediate ;
 tran_high_t s0 , s1 , s2 , s3 , s4 , s5 , s6 , s7 ;
 tran_high_t t0 , t1 , t2 , t3 ;
 tran_high_t x0 , x1 , x2 , x3 ;
 int i ;
 for ( i = 0 ;
 i < 8 ;
 i ++ ) {
 s0 = ( input [ 0 * stride ] + input [ 7 * stride ] ) * 4 ;
 s1 = ( input [ 1 * stride ] + input [ 6 * stride ] ) * 4 ;
 s2 = ( input [ 2 * stride ] + input [ 5 * stride ] ) * 4 ;
 s3 = ( input [ 3 * stride ] + input [ 4 * stride ] ) * 4 ;
 s4 = ( input [ 3 * stride ] - input [ 4 * stride ] ) * 4 ;
 s5 = ( input [ 2 * stride ] - input [ 5 * stride ] ) * 4 ;
 s6 = ( input [ 1 * stride ] - input [ 6 * stride ] ) * 4 ;
 s7 = ( input [ 0 * stride ] - input [ 7 * stride ] ) * 4 ;
 x0 = s0 + s3 ;
 x1 = s1 + s2 ;
 x2 = s1 - s2 ;
 x3 = s0 - s3 ;
 t0 = ( x0 + x1 ) * cospi_16_64 ;
 t1 = ( x0 - x1 ) * cospi_16_64 ;
 t2 = x2 * cospi_24_64 + x3 * cospi_8_64 ;
 t3 = - x2 * cospi_8_64 + x3 * cospi_24_64 ;
 output [ 0 * 8 ] = fdct_round_shift ( t0 ) ;
 output [ 2 * 8 ] = fdct_round_shift ( t2 ) ;
 output [ 4 * 8 ] = fdct_round_shift ( t1 ) ;
 output [ 6 * 8 ] = fdct_round_shift ( t3 ) ;
 t0 = ( s6 - s5 ) * cospi_16_64 ;
 t1 = ( s6 + s5 ) * cospi_16_64 ;
 t2 = fdct_round_shift ( t0 ) ;
 t3 = fdct_round_shift ( t1 ) ;
 x0 = s4 + t2 ;
 x1 = s4 - t2 ;
 x2 = s7 - t3 ;
 x3 = s7 + t3 ;
 t0 = x0 * cospi_28_64 + x3 * cospi_4_64 ;
 t1 = x1 * cospi_12_64 + x2 * cospi_20_64 ;
 t2 = x2 * cospi_12_64 + x1 * - cospi_20_64 ;
 t3 = x3 * cospi_28_64 + x0 * - cospi_4_64 ;
 output [ 1 * 8 ] = fdct_round_shift ( t0 ) ;
 output [ 3 * 8 ] = fdct_round_shift ( t2 ) ;
 output [ 5 * 8 ] = fdct_round_shift ( t1 ) ;
 output [ 7 * 8 ] = fdct_round_shift ( t3 ) ;
 input ++ ;
 output ++ ;
 }
 }
 for ( i = 0 ;
 i < 8 ;
 ++ i ) {
 fdct8 ( & intermediate [ i * 8 ] , & final_output [ i * 8 ] ) ;
 for ( j = 0 ;
 j < 8 ;
 ++ j ) final_output [ j + i * 8 ] /= 2 ;
 }
 }