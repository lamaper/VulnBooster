void vp9_iht4x4_16_add_sse2 ( const int16_t * input , uint8_t * dest , int stride , int tx_type ) {
 __m128i in [ 2 ] ;
 const __m128i zero = _mm_setzero_si128 ( ) ;
 const __m128i eight = _mm_set1_epi16 ( 8 ) ;
 in [ 0 ] = _mm_loadu_si128 ( ( const __m128i * ) ( input ) ) ;
 in [ 1 ] = _mm_loadu_si128 ( ( const __m128i * ) ( input + 8 ) ) ;
 switch ( tx_type ) {
 case 0 : idct4_sse2 ( in ) ;
 idct4_sse2 ( in ) ;
 break ;
 case 1 : idct4_sse2 ( in ) ;
 iadst4_sse2 ( in ) ;
 break ;
 case 2 : iadst4_sse2 ( in ) ;
 idct4_sse2 ( in ) ;
 break ;
 case 3 : iadst4_sse2 ( in ) ;
 iadst4_sse2 ( in ) ;
 break ;
 default : assert ( 0 ) ;
 break ;
 }
 in [ 0 ] = _mm_add_epi16 ( in [ 0 ] , eight ) ;
 in [ 1 ] = _mm_add_epi16 ( in [ 1 ] , eight ) ;
 in [ 0 ] = _mm_srai_epi16 ( in [ 0 ] , 4 ) ;
 in [ 1 ] = _mm_srai_epi16 ( in [ 1 ] , 4 ) ;
 {
 __m128i d0 = _mm_cvtsi32_si128 ( * ( const int * ) ( dest ) ) ;
 __m128i d2 = _mm_cvtsi32_si128 ( * ( const int * ) ( dest + stride * 2 ) ) ;
 d0 = _mm_unpacklo_epi32 ( d0 , _mm_cvtsi32_si128 ( * ( const int * ) ( dest + stride ) ) ) ;
 d2 = _mm_unpacklo_epi32 ( d2 , _mm_cvtsi32_si128 ( * ( const int * ) ( dest + stride * 3 ) ) ) ;
 d0 = _mm_unpacklo_epi8 ( d0 , zero ) ;
 d2 = _mm_unpacklo_epi8 ( d2 , zero ) ;
 d0 = _mm_add_epi16 ( d0 , in [ 0 ] ) ;
 d2 = _mm_add_epi16 ( d2 , in [ 1 ] ) ;
 d0 = _mm_packus_epi16 ( d0 , d2 ) ;
 * ( int * ) dest = _mm_cvtsi128_si32 ( d0 ) ;
 d0 = _mm_srli_si128 ( d0 , 4 ) ;
 * ( int * ) ( dest + stride ) = _mm_cvtsi128_si32 ( d0 ) ;
 d0 = _mm_srli_si128 ( d0 , 4 ) ;
 * ( int * ) ( dest + stride * 2 ) = _mm_cvtsi128_si32 ( d0 ) ;
 d0 = _mm_srli_si128 ( d0 , 4 ) ;
 * ( int * ) ( dest + stride * 3 ) = _mm_cvtsi128_si32 ( d0 ) ;
 }
 }