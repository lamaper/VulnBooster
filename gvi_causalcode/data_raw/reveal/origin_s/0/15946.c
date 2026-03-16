static double rfc1867_size ( tvbuff_t * tvb , int offset ) {
 guint8 val ;
 double size ;
 guint32 exponent ;
 val = tvb_get_guint8 ( tvb , offset ) ;
 size = ( val & 0xF0 ) >> 4 ;
 exponent = ( val & 0x0F ) ;
 while ( exponent != 0 ) {
 size *= 10 ;
 exponent -- ;
 }
 return size / 100 ;
 }