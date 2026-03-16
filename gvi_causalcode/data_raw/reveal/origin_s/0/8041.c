void vp9_idct32x32_1_add_sse2 ( const int16_t * input , uint8_t * dest , int stride ) {
 __m128i dc_value ;
 const __m128i zero = _mm_setzero_si128 ( ) ;
 int a , i ;
 a = dct_const_round_shift ( input [ 0 ] * cospi_16_64 ) ;
 a = dct_const_round_shift ( a * cospi_16_64 ) ;
 a = ROUND_POWER_OF_TWO ( a , 6 ) ;
 dc_value = _mm_set1_epi16 ( a ) ;
 for ( i = 0 ;
 i < 4 ;
 ++ i ) {
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 RECON_AND_STORE ( dest , dc_value ) ;
 dest += 8 - ( stride * 32 ) ;
 }
 }