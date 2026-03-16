static int8_t highBit ( int32_t value ) {
 int8_t bit = 0 ;
 if ( value <= 0 ) {
 return - 32 ;
 }
 if ( value >= 1 << 16 ) {
 value >>= 16 ;
 bit += 16 ;
 }
 if ( value >= 1 << 8 ) {
 value >>= 8 ;
 bit += 8 ;
 }
 if ( value >= 1 << 4 ) {
 value >>= 4 ;
 bit += 4 ;
 }
 if ( value >= 1 << 2 ) {
 value >>= 2 ;
 bit += 2 ;
 }
 if ( value >= 1 << 1 ) {
 bit += 1 ;
 }
 return bit ;
 }