static int dot_product ( const int16_t * a , const int16_t * b , int length ) {
 int i , sum = 0 ;
 for ( i = 0 ;
 i < length ;
 i ++ ) {
 int prod = a [ i ] * b [ i ] ;
 sum = av_sat_dadd32 ( sum , prod ) ;
 }
 return sum ;
 }