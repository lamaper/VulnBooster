static void U_CALLCONV lenient8IteratorSetState ( UCharIterator * iter , uint32_t state , UErrorCode * pErrorCode ) {
 if ( pErrorCode == NULL || U_FAILURE ( * pErrorCode ) ) {
 }
 else if ( iter == NULL ) {
 * pErrorCode = U_ILLEGAL_ARGUMENT_ERROR ;
 }
 else if ( state == lenient8IteratorGetState ( iter ) ) {
 }
 else {
 int32_t index = ( int32_t ) ( state >> 1 ) ;
 state &= 1 ;
 if ( ( state == 0 ? index < 0 : index < 4 ) || iter -> limit < index ) {
 * pErrorCode = U_INDEX_OUTOFBOUNDS_ERROR ;
 }
 else {
 iter -> start = index ;
 if ( index <= 1 ) {
 iter -> index = index ;
 }
 else {
 iter -> index = - 1 ;
 }
 if ( state == 0 ) {
 iter -> reservedField = 0 ;
 }
 else {
 UChar32 c ;
 L8_PREV ( ( const uint8_t * ) iter -> context , 0 , index , c ) ;
 if ( c <= 0xffff ) {
 * pErrorCode = U_INDEX_OUTOFBOUNDS_ERROR ;
 }
 else {
 iter -> reservedField = c ;
 }
 }
 }
 }
 }