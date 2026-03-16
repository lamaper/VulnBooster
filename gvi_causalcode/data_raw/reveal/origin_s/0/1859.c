static int block_sse ( uint8_t * const * buf1 , uint8_t * const * buf2 , int x1 , int y1 , int x2 , int y2 , const int * stride1 , const int * stride2 , int size ) {
 int i , k ;
 int sse = 0 ;
 for ( k = 0 ;
 k < 3 ;
 k ++ ) {
 int bias = ( k ? CHROMA_BIAS : 4 ) ;
 for ( i = 0 ;
 i < size ;
 i ++ ) sse += bias * eval_sse ( buf1 [ k ] + ( y1 + i ) * stride1 [ k ] + x1 , buf2 [ k ] + ( y2 + i ) * stride2 [ k ] + x2 , size ) ;
 }
 return sse ;
 }