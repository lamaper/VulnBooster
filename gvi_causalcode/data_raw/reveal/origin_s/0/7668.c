static void idct4_sse2 ( __m128i * in ) {
 const __m128i k__cospi_p16_p16 = pair_set_epi16 ( cospi_16_64 , cospi_16_64 ) ;
 const __m128i k__cospi_p16_m16 = pair_set_epi16 ( cospi_16_64 , - cospi_16_64 ) ;
 const __m128i k__cospi_p24_m08 = pair_set_epi16 ( cospi_24_64 , - cospi_8_64 ) ;
 const __m128i k__cospi_p08_p24 = pair_set_epi16 ( cospi_8_64 , cospi_24_64 ) ;
 const __m128i k__DCT_CONST_ROUNDING = _mm_set1_epi32 ( DCT_CONST_ROUNDING ) ;
 __m128i u [ 8 ] , v [ 8 ] ;
 transpose_4x4 ( in ) ;
 u [ 0 ] = _mm_unpacklo_epi16 ( in [ 0 ] , in [ 1 ] ) ;
 u [ 1 ] = _mm_unpackhi_epi16 ( in [ 0 ] , in [ 1 ] ) ;
 v [ 0 ] = _mm_madd_epi16 ( u [ 0 ] , k__cospi_p16_p16 ) ;
 v [ 1 ] = _mm_madd_epi16 ( u [ 0 ] , k__cospi_p16_m16 ) ;
 v [ 2 ] = _mm_madd_epi16 ( u [ 1 ] , k__cospi_p24_m08 ) ;
 v [ 3 ] = _mm_madd_epi16 ( u [ 1 ] , k__cospi_p08_p24 ) ;
 u [ 0 ] = _mm_add_epi32 ( v [ 0 ] , k__DCT_CONST_ROUNDING ) ;
 u [ 1 ] = _mm_add_epi32 ( v [ 1 ] , k__DCT_CONST_ROUNDING ) ;
 u [ 2 ] = _mm_add_epi32 ( v [ 2 ] , k__DCT_CONST_ROUNDING ) ;
 u [ 3 ] = _mm_add_epi32 ( v [ 3 ] , k__DCT_CONST_ROUNDING ) ;
 v [ 0 ] = _mm_srai_epi32 ( u [ 0 ] , DCT_CONST_BITS ) ;
 v [ 1 ] = _mm_srai_epi32 ( u [ 1 ] , DCT_CONST_BITS ) ;
 v [ 2 ] = _mm_srai_epi32 ( u [ 2 ] , DCT_CONST_BITS ) ;
 v [ 3 ] = _mm_srai_epi32 ( u [ 3 ] , DCT_CONST_BITS ) ;
 u [ 0 ] = _mm_packs_epi32 ( v [ 0 ] , v [ 1 ] ) ;
 u [ 1 ] = _mm_packs_epi32 ( v [ 3 ] , v [ 2 ] ) ;
 in [ 0 ] = _mm_add_epi16 ( u [ 0 ] , u [ 1 ] ) ;
 in [ 1 ] = _mm_sub_epi16 ( u [ 0 ] , u [ 1 ] ) ;
 in [ 1 ] = _mm_shuffle_epi32 ( in [ 1 ] , 0x4E ) ;
 }