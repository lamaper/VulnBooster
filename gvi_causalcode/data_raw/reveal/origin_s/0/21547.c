static int64_t get_sse ( const uint8_t * a , int a_stride , const uint8_t * b , int b_stride , int width , int height ) {
 const int dw = width % 16 ;
 const int dh = height % 16 ;
 int64_t total_sse = 0 ;
 unsigned int sse = 0 ;
 int sum = 0 ;
 int x , y ;
 if ( dw > 0 ) {
 variance ( & a [ width - dw ] , a_stride , & b [ width - dw ] , b_stride , dw , height , & sse , & sum ) ;
 total_sse += sse ;
 }
 if ( dh > 0 ) {
 variance ( & a [ ( height - dh ) * a_stride ] , a_stride , & b [ ( height - dh ) * b_stride ] , b_stride , width - dw , dh , & sse , & sum ) ;
 total_sse += sse ;
 }
 for ( y = 0 ;
 y < height / 16 ;
 ++ y ) {
 const uint8_t * pa = a ;
 const uint8_t * pb = b ;
 for ( x = 0 ;
 x < width / 16 ;
 ++ x ) {
 vp9_mse16x16 ( pa , a_stride , pb , b_stride , & sse ) ;
 total_sse += sse ;
 pa += 16 ;
 pb += 16 ;
 }
 a += 16 * a_stride ;
 b += 16 * b_stride ;
 }
 return total_sse ;
 }