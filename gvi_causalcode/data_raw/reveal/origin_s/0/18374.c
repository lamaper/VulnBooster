static unsigned int variance8x8_neon ( const uint8_t * a , int a_stride , const uint8_t * b , int b_stride , unsigned int * sse ) {
 int sum ;
 variance_neon_w8 ( a , a_stride , b , b_stride , kWidth8 , kHeight8 , sse , & sum ) ;
 return * sse - ( ( ( int64_t ) sum * sum ) / ( kWidth8 * kHeight8 ) ) ;
 }