static int32_t U_CALLCONV lenient8IteratorMove ( UCharIterator * iter , int32_t delta , UCharIteratorOrigin origin ) {
 const uint8_t * s ;
 UChar32 c ;
 int32_t pos ;
 int32_t i ;
 UBool havePos ;
 switch ( origin ) {
 case UITER_ZERO : case UITER_START : pos = delta ;
 havePos = TRUE ;
 break ;
 case UITER_CURRENT : if ( iter -> index >= 0 ) {
 pos = iter -> index + delta ;
 havePos = TRUE ;
 }
 else {
 pos = 0 ;
 havePos = FALSE ;
 }
 break ;
 case UITER_LIMIT : case UITER_LENGTH : if ( iter -> length >= 0 ) {
 pos = iter -> length + delta ;
 havePos = TRUE ;
 }
 else {
 iter -> index = - 1 ;
 iter -> start = iter -> limit ;
 iter -> reservedField = 0 ;
 if ( delta >= 0 ) {
 return UITER_UNKNOWN_INDEX ;
 }
 else {
 pos = 0 ;
 havePos = FALSE ;
 }
 }
 break ;
 default : return - 1 ;
 }
 if ( havePos ) {
 if ( pos <= 0 ) {
 iter -> index = iter -> start = iter -> reservedField = 0 ;
 return 0 ;
 }
 else if ( iter -> length >= 0 && pos >= iter -> length ) {
 iter -> index = iter -> length ;
 iter -> start = iter -> limit ;
 iter -> reservedField = 0 ;
 return iter -> index ;
 }
 if ( iter -> index < 0 || pos < iter -> index / 2 ) {
 iter -> index = iter -> start = iter -> reservedField = 0 ;
 }
 else if ( iter -> length >= 0 && ( iter -> length - pos ) < ( pos - iter -> index ) ) {
 iter -> index = iter -> length ;
 iter -> start = iter -> limit ;
 iter -> reservedField = 0 ;
 }
 delta = pos - iter -> index ;
 if ( delta == 0 ) {
 return iter -> index ;
 }
 }
 else {
 if ( delta == 0 ) {
 return UITER_UNKNOWN_INDEX ;
 }
 else if ( - delta >= iter -> start ) {
 iter -> index = iter -> start = iter -> reservedField = 0 ;
 return 0 ;
 }
 else if ( delta >= ( iter -> limit - iter -> start ) ) {
 iter -> index = iter -> length ;
 iter -> start = iter -> limit ;
 iter -> reservedField = 0 ;
 return iter -> index >= 0 ? iter -> index : UITER_UNKNOWN_INDEX ;
 }
 }
 s = ( const uint8_t * ) iter -> context ;
 pos = iter -> index ;
 i = iter -> start ;
 if ( delta > 0 ) {
 int32_t limit = iter -> limit ;
 if ( iter -> reservedField != 0 ) {
 iter -> reservedField = 0 ;
 ++ pos ;
 -- delta ;
 }
 while ( delta > 0 && i < limit ) {
 L8_NEXT ( s , i , limit , c ) ;
 if ( c < 0xffff ) {
 ++ pos ;
 -- delta ;
 }
 else if ( delta >= 2 ) {
 pos += 2 ;
 delta -= 2 ;
 }
 else {
 iter -> reservedField = c ;
 ++ pos ;
 break ;
 }
 }
 if ( i == limit ) {
 if ( iter -> length < 0 && iter -> index >= 0 ) {
 iter -> length = iter -> reservedField == 0 ? pos : pos + 1 ;
 }
 else if ( iter -> index < 0 && iter -> length >= 0 ) {
 iter -> index = iter -> reservedField == 0 ? iter -> length : iter -> length - 1 ;
 }
 }
 }
 else {
 if ( iter -> reservedField != 0 ) {
 iter -> reservedField = 0 ;
 i -= 4 ;
 -- pos ;
 ++ delta ;
 }
 while ( delta < 0 && i > 0 ) {
 L8_PREV ( s , 0 , i , c ) ;
 if ( c < 0xffff ) {
 -- pos ;
 ++ delta ;
 }
 else if ( delta <= - 2 ) {
 pos -= 2 ;
 delta += 2 ;
 }
 else {
 i += 4 ;
 iter -> reservedField = c ;
 -- pos ;
 break ;
 }
 }
 }
 iter -> start = i ;
 if ( iter -> index >= 0 ) {
 return iter -> index = pos ;
 }
 else {
 if ( i <= 1 ) {
 return iter -> index = i ;
 }
 else {
 return UITER_UNKNOWN_INDEX ;
 }
 }
 }