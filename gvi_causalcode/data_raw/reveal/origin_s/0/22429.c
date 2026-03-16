static inline unsigned make_16bit ( unsigned value ) {
 value &= 0xFFC0 ;
 return value + ( value >> 10 ) ;
 }