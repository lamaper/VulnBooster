static UChar32 U_CALLCONV lenient8IteratorPrevious ( UCharIterator * iter ) {
 int32_t index ;
 if ( iter -> reservedField != 0 ) {
 UChar lead = U16_LEAD ( iter -> reservedField ) ;
 iter -> reservedField = 0 ;
 iter -> start -= 4 ;
 if ( ( index = iter -> index ) > 0 ) {
 iter -> index = index - 1 ;
 }
 return lead ;
 }
 else if ( iter -> start > 0 ) {
 const uint8_t * s = ( const uint8_t * ) iter -> context ;
 UChar32 c ;
 L8_PREV ( s , 0 , iter -> start , c ) ;
 if ( ( index = iter -> index ) > 0 ) {
 iter -> index = index - 1 ;
 }
 else if ( iter -> start <= 1 ) {
 iter -> index = c <= 0xffff ? iter -> start : iter -> start + 1 ;
 }
 if ( c < 0 ) {
 return 0xfffd ;
 }
 else if ( c <= 0xffff ) {
 return c ;
 }
 else {
 iter -> start += 4 ;
 iter -> reservedField = c ;
 return U16_TRAIL ( c ) ;
 }
 }
 else {
 return U_SENTINEL ;
 }
 }