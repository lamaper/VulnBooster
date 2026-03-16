static void U_CALLCONV _UTF16BEFromUnicodeWithOffsets ( UConverterFromUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv ;
 const UChar * source ;
 char * target ;
 int32_t * offsets ;
 uint32_t targetCapacity , length , sourceIndex ;
 UChar c , trail ;
 char overflow [ 4 ] ;
 source = pArgs -> source ;
 length = ( int32_t ) ( pArgs -> sourceLimit - source ) ;
 if ( length <= 0 ) {
 return ;
 }
 cnv = pArgs -> converter ;
 if ( cnv -> fromUnicodeStatus == UCNV_NEED_TO_WRITE_BOM ) {
 static const char bom [ ] = {
 ( char ) 0xfe , ( char ) 0xff }
 ;
 ucnv_fromUWriteBytes ( cnv , bom , 2 , & pArgs -> target , pArgs -> targetLimit , & pArgs -> offsets , - 1 , pErrorCode ) ;
 cnv -> fromUnicodeStatus = 0 ;
 }
 target = pArgs -> target ;
 if ( target >= pArgs -> targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return ;
 }
 targetCapacity = ( uint32_t ) ( pArgs -> targetLimit - target ) ;
 offsets = pArgs -> offsets ;
 sourceIndex = 0 ;
 if ( ( c = ( UChar ) cnv -> fromUChar32 ) != 0 && U16_IS_TRAIL ( trail = * source ) && targetCapacity >= 4 ) {
 ++ source ;
 -- length ;
 target [ 0 ] = ( uint8_t ) ( c >> 8 ) ;
 target [ 1 ] = ( uint8_t ) c ;
 target [ 2 ] = ( uint8_t ) ( trail >> 8 ) ;
 target [ 3 ] = ( uint8_t ) trail ;
 target += 4 ;
 targetCapacity -= 4 ;
 if ( offsets != NULL ) {
 * offsets ++ = - 1 ;
 * offsets ++ = - 1 ;
 * offsets ++ = - 1 ;
 * offsets ++ = - 1 ;
 }
 sourceIndex = 1 ;
 cnv -> fromUChar32 = c = 0 ;
 }
 if ( c == 0 ) {
 uint32_t count = 2 * length ;
 if ( count > targetCapacity ) {
 count = targetCapacity & ~ 1 ;
 }
 targetCapacity -= count ;
 count >>= 1 ;
 length -= count ;
 if ( offsets == NULL ) {
 while ( count > 0 ) {
 c = * source ++ ;
 if ( U16_IS_SINGLE ( c ) ) {
 target [ 0 ] = ( uint8_t ) ( c >> 8 ) ;
 target [ 1 ] = ( uint8_t ) c ;
 target += 2 ;
 }
 else if ( U16_IS_SURROGATE_LEAD ( c ) && count >= 2 && U16_IS_TRAIL ( trail = * source ) ) {
 ++ source ;
 -- count ;
 target [ 0 ] = ( uint8_t ) ( c >> 8 ) ;
 target [ 1 ] = ( uint8_t ) c ;
 target [ 2 ] = ( uint8_t ) ( trail >> 8 ) ;
 target [ 3 ] = ( uint8_t ) trail ;
 target += 4 ;
 }
 else {
 break ;
 }
 -- count ;
 }
 }
 else {
 while ( count > 0 ) {
 c = * source ++ ;
 if ( U16_IS_SINGLE ( c ) ) {
 target [ 0 ] = ( uint8_t ) ( c >> 8 ) ;
 target [ 1 ] = ( uint8_t ) c ;
 target += 2 ;
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ++ ;
 }
 else if ( U16_IS_SURROGATE_LEAD ( c ) && count >= 2 && U16_IS_TRAIL ( trail = * source ) ) {
 ++ source ;
 -- count ;
 target [ 0 ] = ( uint8_t ) ( c >> 8 ) ;
 target [ 1 ] = ( uint8_t ) c ;
 target [ 2 ] = ( uint8_t ) ( trail >> 8 ) ;
 target [ 3 ] = ( uint8_t ) trail ;
 target += 4 ;
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ;
 sourceIndex += 2 ;
 }
 else {
 break ;
 }
 -- count ;
 }
 }
 if ( count == 0 ) {
 if ( length > 0 && targetCapacity > 0 ) {
 if ( U16_IS_SINGLE ( c = * source ++ ) ) {
 overflow [ 0 ] = ( char ) ( c >> 8 ) ;
 overflow [ 1 ] = ( char ) c ;
 length = 2 ;
 c = 0 ;
 }
 }
 else {
 length = 0 ;
 c = 0 ;
 }
 }
 else {
 targetCapacity += 2 * count ;
 }
 }
 else {
 length = 0 ;
 }
 if ( c != 0 ) {
 length = 0 ;
 if ( U16_IS_SURROGATE_LEAD ( c ) ) {
 if ( source < pArgs -> sourceLimit ) {
 if ( U16_IS_TRAIL ( trail = * source ) ) {
 ++ source ;
 overflow [ 0 ] = ( char ) ( c >> 8 ) ;
 overflow [ 1 ] = ( char ) c ;
 overflow [ 2 ] = ( char ) ( trail >> 8 ) ;
 overflow [ 3 ] = ( char ) trail ;
 length = 4 ;
 c = 0 ;
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 }
 }
 else {
 }
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 }
 cnv -> fromUChar32 = c ;
 }
 if ( length > 0 ) {
 ucnv_fromUWriteBytes ( cnv , overflow , length , ( char * * ) & target , pArgs -> targetLimit , & offsets , sourceIndex , pErrorCode ) ;
 targetCapacity = ( uint32_t ) ( pArgs -> targetLimit - ( char * ) target ) ;
 }
 if ( U_SUCCESS ( * pErrorCode ) && source < pArgs -> sourceLimit && targetCapacity == 0 ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 pArgs -> source = source ;
 pArgs -> target = ( char * ) target ;
 pArgs -> offsets = offsets ;
 }