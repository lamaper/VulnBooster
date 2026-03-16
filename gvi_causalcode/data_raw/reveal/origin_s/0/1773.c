static int32_t U_CALLCONV lenient8IteratorGetIndex ( UCharIterator * iter , UCharIteratorOrigin origin ) {
 switch ( origin ) {
 case UITER_ZERO : case UITER_START : return 0 ;
 case UITER_CURRENT : if ( iter -> index < 0 ) {
 const uint8_t * s ;
 UChar32 c ;
 int32_t i , limit , index ;
 s = ( const uint8_t * ) iter -> context ;
 i = index = 0 ;
 limit = iter -> start ;
 while ( i < limit ) {
 L8_NEXT ( s , i , limit , c ) ;
 if ( c <= 0xffff ) {
 ++ index ;
 }
 else {
 index += 2 ;
 }
 }
 iter -> start = i ;
 if ( i == iter -> limit ) {
 iter -> length = index ;
 }
 if ( iter -> reservedField != 0 ) {
 -- index ;
 }
 iter -> index = index ;
 }
 return iter -> index ;
 case UITER_LIMIT : case UITER_LENGTH : if ( iter -> length < 0 ) {
 const uint8_t * s ;
 UChar32 c ;
 int32_t i , limit , length ;
 s = ( const uint8_t * ) iter -> context ;
 if ( iter -> index < 0 ) {
 i = length = 0 ;
 limit = iter -> start ;
 while ( i < limit ) {
 L8_NEXT ( s , i , limit , c ) ;
 if ( c <= 0xffff ) {
 ++ length ;
 }
 else {
 length += 2 ;
 }
 }
 iter -> start = i ;
 iter -> index = iter -> reservedField != 0 ? length - 1 : length ;
 }
 else {
 i = iter -> start ;
 length = iter -> index ;
 if ( iter -> reservedField != 0 ) {
 ++ length ;
 }
 }
 limit = iter -> limit ;
 while ( i < limit ) {
 L8_NEXT ( s , i , limit , c ) ;
 if ( c <= 0xffff ) {
 ++ length ;
 }
 else {
 length += 2 ;
 }
 }
 iter -> length = length ;
 }
 return iter -> length ;
 default : return - 1 ;
 }
 }