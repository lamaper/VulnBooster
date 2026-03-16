void vp9_idct32x32_1_add_c ( const tran_low_t * input , uint8_t * dest , int stride ) {
 int i , j ;
 tran_high_t a1 ;
 tran_low_t out = dct_const_round_shift ( input [ 0 ] * cospi_16_64 ) ;
 out = dct_const_round_shift ( out * cospi_16_64 ) ;
 a1 = ROUND_POWER_OF_TWO ( out , 6 ) ;
 for ( j = 0 ;
 j < 32 ;
 ++ j ) {
 for ( i = 0 ;
 i < 32 ;
 ++ i ) dest [ i ] = clip_pixel ( dest [ i ] + a1 ) ;
 dest += stride ;
 }
 }