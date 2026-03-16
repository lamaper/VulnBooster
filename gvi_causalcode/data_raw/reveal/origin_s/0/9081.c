static void invert_quant ( int improved_quant , short * quant , short * shift , short d ) {
 if ( improved_quant ) {
 unsigned t ;
 int l ;
 t = d ;
 for ( l = 0 ;
 t > 1 ;
 l ++ ) t >>= 1 ;
 t = 1 + ( 1 << ( 16 + l ) ) / d ;
 * quant = ( short ) ( t - ( 1 << 16 ) ) ;
 * shift = l ;
 * shift = 1 << ( 16 - * shift ) ;
 }
 else {
 * quant = ( 1 << 16 ) / d ;
 * shift = 0 ;
 * shift = 1 << ( 16 - * shift ) ;
 }
 }