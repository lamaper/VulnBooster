void variance ( const uint8_t * a , int a_stride , const uint8_t * b , int b_stride , int w , int h , unsigned int * sse , int * sum ) {
 int i , j ;
 * sum = 0 ;
 * sse = 0 ;
 for ( i = 0 ;
 i < h ;
 i ++ ) {
 for ( j = 0 ;
 j < w ;
 j ++ ) {
 const int diff = a [ j ] - b [ j ] ;
 * sum += diff ;
 * sse += diff * diff ;
 }
 a += a_stride ;
 b += b_stride ;
 }
 }