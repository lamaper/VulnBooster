unsigned char clamp_u8 ( float v ) {
 if ( v > 255. ) return 255 ;
 else if ( v < 0 ) return 0 ;
 else return floor ( v + .5 ) ;
 }