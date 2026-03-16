static inline void sub_left_prediction_bgr32 ( HYuvContext * s , uint8_t * dst , const uint8_t * src , int w , int * red , int * green , int * blue , int * alpha ) {
 int i ;
 int r , g , b , a ;
 r = * red ;
 g = * green ;
 b = * blue ;
 a = * alpha ;
 for ( i = 0 ;
 i < FFMIN ( w , 4 ) ;
 i ++ ) {
 const int rt = src [ i * 4 + R ] ;
 const int gt = src [ i * 4 + G ] ;
 const int bt = src [ i * 4 + B ] ;
 const int at = src [ i * 4 + A ] ;
 dst [ i * 4 + R ] = rt - r ;
 dst [ i * 4 + G ] = gt - g ;
 dst [ i * 4 + B ] = bt - b ;
 dst [ i * 4 + A ] = at - a ;
 r = rt ;
 g = gt ;
 b = bt ;
 a = at ;
 }
 s -> dsp . diff_bytes ( dst + 16 , src + 16 , src + 12 , w * 4 - 16 ) ;
 * red = src [ ( w - 1 ) * 4 + R ] ;
 * green = src [ ( w - 1 ) * 4 + G ] ;
 * blue = src [ ( w - 1 ) * 4 + B ] ;
 * alpha = src [ ( w - 1 ) * 4 + A ] ;
 }