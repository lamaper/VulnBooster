void vp9_idct8x8_1_add_sse2 ( const int16_t * input , uint8_t * dest , int stride ) {
 __m128i dc_value ;
 const __m128i zero = _mm_setzero_si128 ( ) ;
 int a ;
 a = dct_const_round_shift ( input [ 0 ] * cospi_16_64 ) ;
 a = dct_const_round_shift ( a * cospi_16_64 ) ;
 a = ROUND_POWER_OF_TWO ( a , 5 ) ;
 dc_value = _mm_set1_epi16 ( a ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 }