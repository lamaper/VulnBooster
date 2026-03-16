static inline void sub_left_prediction_rgb24 ( HYuvContext * s , uint8_t * dst , const uint8_t * src , int w , int * red , int * green , int * blue ) {
 int i ;
 int r , g , b ;
 r = * red ;
 g = * green ;
 b = * blue ;
 for ( i = 0 ;
 i < FFMIN ( w , 16 ) ;
 i ++ ) {
 const int rt = src [ i * 3 + 0 ] ;
 const int gt = src [ i * 3 + 1 ] ;
 const int bt = src [ i * 3 + 2 ] ;
 dst [ i * 3 + 0 ] = rt - r ;
 dst [ i * 3 + 1 ] = gt - g ;
 dst [ i * 3 + 2 ] = bt - b ;
 r = rt ;
 g = gt ;
 b = bt ;
 }
 s -> dsp . diff_bytes ( dst + 48 , src + 48 , src + 48 - 3 , w * 3 - 48 ) ;
 * red = src [ ( w - 1 ) * 3 + 0 ] ;
 * green = src [ ( w - 1 ) * 3 + 1 ] ;
 * blue = src [ ( w - 1 ) * 3 + 2 ] ;
 }