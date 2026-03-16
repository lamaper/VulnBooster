static void _UTF7ToUnicodeWithOffsets ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv ;
 const uint8_t * source , * sourceLimit ;
 UChar * target ;
 const UChar * targetLimit ;
 int32_t * offsets ;
 uint8_t * bytes ;
 uint8_t byteIndex ;
 int32_t length , targetCapacity ;
 uint16_t bits ;
 int8_t base64Counter ;
 UBool inDirectMode ;
 int8_t base64Value ;
 int32_t sourceIndex , nextSourceIndex ;
 uint8_t b ;
 cnv = pArgs -> converter ;
 source = ( const uint8_t * ) pArgs -> source ;
 sourceLimit = ( const uint8_t * ) pArgs -> sourceLimit ;
 target = pArgs -> target ;
 targetLimit = pArgs -> targetLimit ;
 offsets = pArgs -> offsets ;
 {
 uint32_t status = cnv -> toUnicodeStatus ;
 inDirectMode = ( UBool ) ( ( status >> 24 ) & 1 ) ;
 base64Counter = ( int8_t ) ( status >> 16 ) ;
 bits = ( uint16_t ) status ;
 }
 bytes = cnv -> toUBytes ;
 byteIndex = cnv -> toULength ;
 sourceIndex = byteIndex == 0 ? 0 : - 1 ;
 nextSourceIndex = 0 ;
 if ( inDirectMode ) {
 directMode : byteIndex = 0 ;
 length = ( int32_t ) ( sourceLimit - source ) ;
 targetCapacity = ( int32_t ) ( targetLimit - target ) ;
 if ( length > targetCapacity ) {
 length = targetCapacity ;
 }
 while ( length > 0 ) {
 b = * source ++ ;
 if ( ! isLegalUTF7 ( b ) ) {
 bytes [ 0 ] = b ;
 byteIndex = 1 ;
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 else if ( b != PLUS ) {
 * target ++ = b ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ++ ;
 }
 }
 else {
 nextSourceIndex = ++ sourceIndex ;
 inDirectMode = FALSE ;
 byteIndex = 0 ;
 bits = 0 ;
 base64Counter = - 1 ;
 goto unicodeMode ;
 }
 -- length ;
 }
 if ( source < sourceLimit && target >= targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 else {
 unicodeMode : while ( source < sourceLimit ) {
 if ( target < targetLimit ) {
 bytes [ byteIndex ++ ] = b = * source ++ ;
 ++ nextSourceIndex ;
 base64Value = - 3 ;
 if ( b >= 126 || ( base64Value = fromBase64 [ b ] ) == - 3 || base64Value == - 1 ) {
 inDirectMode = TRUE ;
 if ( base64Counter == - 1 ) {
 -- source ;
 bytes [ 0 ] = PLUS ;
 byteIndex = 1 ;
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 else if ( bits != 0 ) {
 -- source ;
 -- byteIndex ;
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 else {
 if ( base64Value == - 3 ) {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 else {
 -- source ;
 sourceIndex = nextSourceIndex - 1 ;
 goto directMode ;
 }
 }
 }
 else if ( base64Value >= 0 ) {
 switch ( base64Counter ) {
 case - 1 : case 0 : bits = base64Value ;
 base64Counter = 1 ;
 break ;
 case 1 : case 3 : case 4 : case 6 : bits = ( uint16_t ) ( ( bits << 6 ) | base64Value ) ;
 ++ base64Counter ;
 break ;
 case 2 : * target ++ = ( UChar ) ( ( bits << 4 ) | ( base64Value >> 2 ) ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 sourceIndex = nextSourceIndex - 1 ;
 }
 bytes [ 0 ] = b ;
 byteIndex = 1 ;
 bits = ( uint16_t ) ( base64Value & 3 ) ;
 base64Counter = 3 ;
 break ;
 case 5 : * target ++ = ( UChar ) ( ( bits << 2 ) | ( base64Value >> 4 ) ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 sourceIndex = nextSourceIndex - 1 ;
 }
 bytes [ 0 ] = b ;
 byteIndex = 1 ;
 bits = ( uint16_t ) ( base64Value & 15 ) ;
 base64Counter = 6 ;
 break ;
 case 7 : * target ++ = ( UChar ) ( ( bits << 6 ) | base64Value ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 sourceIndex = nextSourceIndex ;
 }
 byteIndex = 0 ;
 bits = 0 ;
 base64Counter = 0 ;
 break ;
 default : break ;
 }
 }
 else {
 inDirectMode = TRUE ;
 if ( base64Counter == - 1 ) {
 * target ++ = PLUS ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex - 1 ;
 }
 }
 else {
 if ( bits != 0 ) {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 }
 sourceIndex = nextSourceIndex ;
 goto directMode ;
 }
 }
 else {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 }
 if ( U_SUCCESS ( * pErrorCode ) && pArgs -> flush && source == sourceLimit && bits == 0 ) {
 byteIndex = 0 ;
 }
 cnv -> toUnicodeStatus = ( ( uint32_t ) inDirectMode << 24 ) | ( ( uint32_t ) ( ( uint8_t ) base64Counter ) << 16 ) | ( uint32_t ) bits ;
 cnv -> toULength = byteIndex ;
 pArgs -> source = ( const char * ) source ;
 pArgs -> target = target ;
 pArgs -> offsets = offsets ;
 return ;
 }