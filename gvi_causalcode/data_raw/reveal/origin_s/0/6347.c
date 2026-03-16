static inline int16_t mult ( Float11 * f1 , Float11 * f2 ) {
 int res , exp ;
 exp = f1 -> exp + f2 -> exp ;
 res = ( ( ( f1 -> mant * f2 -> mant ) + 0x30 ) >> 4 ) ;
 res = exp > 19 ? res << ( exp - 19 ) : res >> ( 19 - exp ) ;
 return ( f1 -> sign ^ f2 -> sign ) ? - res : res ;
 }