static inline int sub_left_prediction ( HYuvContext * s , uint8_t * dst , const uint8_t * src , int w , int left ) {
 int i ;
 if ( w < 32 ) {
 for ( i = 0 ;
 i < w ;
 i ++ ) {
 const int temp = src [ i ] ;
 dst [ i ] = temp - left ;
 left = temp ;
 }
 return left ;
 }
 else {
 for ( i = 0 ;
 i < 16 ;
 i ++ ) {
 const int temp = src [ i ] ;
 dst [ i ] = temp - left ;
 left = temp ;
 }
 s -> dsp . diff_bytes ( dst + 16 , src + 16 , src + 15 , w - 16 ) ;
 return src [ w - 1 ] ;
 }
 }