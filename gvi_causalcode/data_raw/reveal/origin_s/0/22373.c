static UChar32 U_CALLCONV lenient8IteratorCurrent ( UCharIterator * iter ) {
 if ( iter -> reservedField != 0 ) {
 return U16_TRAIL ( iter -> reservedField ) ;
 }
 else if ( iter -> start < iter -> limit ) {
 const uint8_t * s = ( const uint8_t * ) iter -> context ;
 UChar32 c ;
 int32_t i = iter -> start ;
 L8_NEXT ( s , i , iter -> limit , c ) ;
 if ( c < 0 ) {
 return 0xfffd ;
 }
 else if ( c <= 0xffff ) {
 return c ;
 }
 else {
 return U16_LEAD ( c ) ;
 }
 }
 else {
 return U_SENTINEL ;
 }
 }