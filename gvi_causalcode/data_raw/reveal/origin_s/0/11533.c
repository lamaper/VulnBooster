static void invert_quant ( int16_t * quant , int16_t * shift , int d ) {
 unsigned t ;
 int l ;
 t = d ;
 for ( l = 0 ;
 t > 1 ;
 l ++ ) t >>= 1 ;
 t = 1 + ( 1 << ( 16 + l ) ) / d ;
 * quant = ( int16_t ) ( t - ( 1 << 16 ) ) ;
 * shift = 1 << ( 16 - l ) ;
 }