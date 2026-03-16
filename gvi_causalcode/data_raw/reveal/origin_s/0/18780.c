static UChar32 U_CALLCONV lenient8IteratorNext ( UCharIterator * iter ) {
 int32_t index ;
 if ( iter -> reservedField != 0 ) {
 UChar trail = U16_TRAIL ( iter -> reservedField ) ;
 iter -> reservedField = 0 ;
 if ( ( index = iter -> index ) >= 0 ) {
 iter -> index = index + 1 ;
 }
 return trail ;
 }
 else if ( iter -> start < iter -> limit ) {
 const uint8_t * s = ( const uint8_t * ) iter -> context ;
 UChar32 c ;
 L8_NEXT ( s , iter -> start , iter -> limit , c ) ;
 if ( ( index = iter -> index ) >= 0 ) {
 iter -> index = ++ index ;
 if ( iter -> length < 0 && iter -> start == iter -> limit ) {
 iter -> length = c <= 0xffff ? index : index + 1 ;
 }
 }
 else if ( iter -> start == iter -> limit && iter -> length >= 0 ) {
 iter -> index = c <= 0xffff ? iter -> length : iter -> length - 1 ;
 }
 if ( c < 0 ) {
 return 0xfffd ;
 }
 else if ( c <= 0xffff ) {
 return c ;
 }
 else {
 iter -> reservedField = c ;
 return U16_LEAD ( c ) ;
 }
 }
 else {
 return U_SENTINEL ;
 }
 }