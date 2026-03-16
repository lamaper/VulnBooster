static void idct8_sse2 ( __m128i * in ) {
 const __m128i rounding = _mm_set1_epi32 ( DCT_CONST_ROUNDING ) ;
 const __m128i stg1_0 = pair_set_epi16 ( cospi_28_64 , - cospi_4_64 ) ;
 const __m128i stg1_1 = pair_set_epi16 ( cospi_4_64 , cospi_28_64 ) ;
 const __m128i stg1_2 = pair_set_epi16 ( - cospi_20_64 , cospi_12_64 ) ;
 const __m128i stg1_3 = pair_set_epi16 ( cospi_12_64 , cospi_20_64 ) ;
 const __m128i stg2_0 = pair_set_epi16 ( cospi_16_64 , cospi_16_64 ) ;
 const __m128i stg2_1 = pair_set_epi16 ( cospi_16_64 , - cospi_16_64 ) ;
 const __m128i stg2_2 = pair_set_epi16 ( cospi_24_64 , - cospi_8_64 ) ;
 const __m128i stg2_3 = pair_set_epi16 ( cospi_8_64 , cospi_24_64 ) ;
 __m128i in0 , in1 , in2 , in3 , in4 , in5 , in6 , in7 ;
 __m128i stp1_0 , stp1_1 , stp1_2 , stp1_3 , stp1_4 , stp1_5 , stp1_6 , stp1_7 ;
 __m128i stp2_0 , stp2_1 , stp2_2 , stp2_3 , stp2_4 , stp2_5 , stp2_6 , stp2_7 ;
 __m128i tmp0 , tmp1 , tmp2 , tmp3 , tmp4 , tmp5 , tmp6 , tmp7 ;
 TRANSPOSE_8X8 ( in [ 0 ] , in [ 1 ] , in [ 2 ] , in [ 3 ] , in [ 4 ] , in [ 5 ] , in [ 6 ] , in [ 7 ] , in0 , in1 , in2 , in3 , in4 , in5 , in6 , in7 ) ;
 IDCT8 ( in0 , in1 , in2 , in3 , in4 , in5 , in6 , in7 , in [ 0 ] , in [ 1 ] , in [ 2 ] , in [ 3 ] , in [ 4 ] , in [ 5 ] , in [ 6 ] , in [ 7 ] ) ;
 }