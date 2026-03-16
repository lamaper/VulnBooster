static void U_CALLCONV _IMAPFromUnicodeWithOffsets ( UConverterFromUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv ;
 const UChar * source , * sourceLimit ;
 uint8_t * target , * targetLimit ;
 int32_t * offsets ;
 int32_t length , targetCapacity , sourceIndex ;
 UChar c ;
 uint8_t b ;
 uint8_t bits ;
 int8_t base64Counter ;
 UBool inDirectMode ;
 cnv = pArgs -> converter ;
 source = pArgs -> source ;
 sourceLimit = pArgs -> sourceLimit ;
 target = ( uint8_t * ) pArgs -> target ;
 targetLimit = ( uint8_t * ) pArgs -> targetLimit ;
 offsets = pArgs -> offsets ;
 {
 uint32_t status = cnv -> fromUnicodeStatus ;
 inDirectMode = ( UBool ) ( ( status >> 24 ) & 1 ) ;
 base64Counter = ( int8_t ) ( status >> 16 ) ;
 bits = ( uint8_t ) status ;
 }
 sourceIndex = 0 ;
 if ( inDirectMode ) {
 directMode : length = ( int32_t ) ( sourceLimit - source ) ;
 targetCapacity = ( int32_t ) ( targetLimit - target ) ;
 if ( length > targetCapacity ) {
 length = targetCapacity ;
 }
 while ( length > 0 ) {
 c = * source ++ ;
 if ( inSetDIMAP ( c ) ) {
 * target ++ = ( uint8_t ) c ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ++ ;
 }
 }
 else if ( c == AMPERSAND ) {
 * target ++ = AMPERSAND ;
 if ( target < targetLimit ) {
 * target ++ = MINUS ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ++ ;
 }
 goto directMode ;
 }
 else {
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ++ ;
 }
 cnv -> charErrorBuffer [ 0 ] = MINUS ;
 cnv -> charErrorBufferLength = 1 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 else {
 -- source ;
 * target ++ = AMPERSAND ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 inDirectMode = FALSE ;
 base64Counter = 0 ;
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
 c = * source ++ ;
 if ( isLegalIMAP ( c ) ) {
 inDirectMode = TRUE ;
 -- source ;
 if ( base64Counter != 0 ) {
 * target ++ = TO_BASE64_IMAP ( bits ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex - 1 ;
 }
 }
 if ( target < targetLimit ) {
 * target ++ = MINUS ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex - 1 ;
 }
 }
 else {
 cnv -> charErrorBuffer [ 0 ] = MINUS ;
 cnv -> charErrorBufferLength = 1 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 goto directMode ;
 }
 else {
 switch ( base64Counter ) {
 case 0 : b = ( uint8_t ) ( c >> 10 ) ;
 * target ++ = TO_BASE64_IMAP ( b ) ;
 if ( target < targetLimit ) {
 b = ( uint8_t ) ( ( c >> 4 ) & 0x3f ) ;
 * target ++ = TO_BASE64_IMAP ( b ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ++ ;
 }
 }
 else {
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ++ ;
 }
 b = ( uint8_t ) ( ( c >> 4 ) & 0x3f ) ;
 cnv -> charErrorBuffer [ 0 ] = TO_BASE64_IMAP ( b ) ;
 cnv -> charErrorBufferLength = 1 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 bits = ( uint8_t ) ( ( c & 15 ) << 2 ) ;
 base64Counter = 1 ;
 break ;
 case 1 : b = ( uint8_t ) ( bits | ( c >> 14 ) ) ;
 * target ++ = TO_BASE64_IMAP ( b ) ;
 if ( target < targetLimit ) {
 b = ( uint8_t ) ( ( c >> 8 ) & 0x3f ) ;
 * target ++ = TO_BASE64_IMAP ( b ) ;
 if ( target < targetLimit ) {
 b = ( uint8_t ) ( ( c >> 2 ) & 0x3f ) ;
 * target ++ = TO_BASE64_IMAP ( b ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ++ ;
 }
 }
 else {
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ++ ;
 }
 b = ( uint8_t ) ( ( c >> 2 ) & 0x3f ) ;
 cnv -> charErrorBuffer [ 0 ] = TO_BASE64_IMAP ( b ) ;
 cnv -> charErrorBufferLength = 1 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 else {
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ++ ;
 }
 b = ( uint8_t ) ( ( c >> 8 ) & 0x3f ) ;
 cnv -> charErrorBuffer [ 0 ] = TO_BASE64_IMAP ( b ) ;
 b = ( uint8_t ) ( ( c >> 2 ) & 0x3f ) ;
 cnv -> charErrorBuffer [ 1 ] = TO_BASE64_IMAP ( b ) ;
 cnv -> charErrorBufferLength = 2 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 bits = ( uint8_t ) ( ( c & 3 ) << 4 ) ;
 base64Counter = 2 ;
 break ;
 case 2 : b = ( uint8_t ) ( bits | ( c >> 12 ) ) ;
 * target ++ = TO_BASE64_IMAP ( b ) ;
 if ( target < targetLimit ) {
 b = ( uint8_t ) ( ( c >> 6 ) & 0x3f ) ;
 * target ++ = TO_BASE64_IMAP ( b ) ;
 if ( target < targetLimit ) {
 b = ( uint8_t ) ( c & 0x3f ) ;
 * target ++ = TO_BASE64_IMAP ( b ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ++ ;
 }
 }
 else {
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ++ ;
 }
 b = ( uint8_t ) ( c & 0x3f ) ;
 cnv -> charErrorBuffer [ 0 ] = TO_BASE64_IMAP ( b ) ;
 cnv -> charErrorBufferLength = 1 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 else {
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ++ ;
 }
 b = ( uint8_t ) ( ( c >> 6 ) & 0x3f ) ;
 cnv -> charErrorBuffer [ 0 ] = TO_BASE64_IMAP ( b ) ;
 b = ( uint8_t ) ( c & 0x3f ) ;
 cnv -> charErrorBuffer [ 1 ] = TO_BASE64_IMAP ( b ) ;
 cnv -> charErrorBufferLength = 2 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 bits = 0 ;
 base64Counter = 0 ;
 break ;
 default : break ;
 }
 }
 }
 else {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 }
 if ( pArgs -> flush && source >= sourceLimit ) {
 if ( ! inDirectMode ) {
 if ( base64Counter != 0 ) {
 if ( target < targetLimit ) {
 * target ++ = TO_BASE64_IMAP ( bits ) ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex - 1 ;
 }
 }
 else {
 cnv -> charErrorBuffer [ cnv -> charErrorBufferLength ++ ] = TO_BASE64_IMAP ( bits ) ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 if ( target < targetLimit ) {
 * target ++ = MINUS ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex - 1 ;
 }
 }
 else {
 cnv -> charErrorBuffer [ cnv -> charErrorBufferLength ++ ] = MINUS ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 cnv -> fromUnicodeStatus = ( cnv -> fromUnicodeStatus & 0xf0000000 ) | 0x1000000 ;
 }
 else {
 cnv -> fromUnicodeStatus = ( cnv -> fromUnicodeStatus & 0xf0000000 ) | ( ( uint32_t ) inDirectMode << 24 ) | ( ( uint32_t ) base64Counter << 16 ) | ( uint32_t ) bits ;
 }
 pArgs -> source = source ;
 pArgs -> target = ( char * ) target ;
 pArgs -> offsets = offsets ;
 return ;
 }