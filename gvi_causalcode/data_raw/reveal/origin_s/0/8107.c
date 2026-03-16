static void iadst16_sse2 ( __m128i * in0 , __m128i * in1 ) {
 array_transpose_16x16 ( in0 , in1 ) ;
 iadst16_8col ( in0 ) ;
 iadst16_8col ( in1 ) ;
 }