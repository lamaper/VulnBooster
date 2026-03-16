static void _UTF16BEToUnicodeWithOffsets ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 UConverter * cnv ;
 const uint8_t * source ;
 UChar * target ;
 int32_t * offsets ;
 uint32_t targetCapacity , length , count , sourceIndex ;
 UChar c , trail ;
 if ( pArgs -> converter -> mode < 8 ) {
 _UTF16ToUnicodeWithOffsets ( pArgs , pErrorCode ) ;
 return ;
 }
 cnv = pArgs -> converter ;
 source = ( const uint8_t * ) pArgs -> source ;
 length = ( int32_t ) ( ( const uint8_t * ) pArgs -> sourceLimit - source ) ;
 if ( length <= 0 && cnv -> toUnicodeStatus == 0 ) {
 return ;
 }
 target = pArgs -> target ;
 if ( target >= pArgs -> targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return ;
 }
 targetCapacity = ( uint32_t ) ( pArgs -> targetLimit - target ) ;
 offsets = pArgs -> offsets ;
 sourceIndex = 0 ;
 c = 0 ;
 if ( cnv -> toUnicodeStatus != 0 ) {
 cnv -> toUBytes [ 0 ] = ( uint8_t ) cnv -> toUnicodeStatus ;
 cnv -> toULength = 1 ;
 cnv -> toUnicodeStatus = 0 ;
 }
 if ( ( count = cnv -> toULength ) != 0 ) {
 uint8_t * p = cnv -> toUBytes ;
 do {
 p [ count ++ ] = * source ++ ;
 ++ sourceIndex ;
 -- length ;
 if ( count == 2 ) {
 c = ( ( UChar ) p [ 0 ] << 8 ) | p [ 1 ] ;
 if ( U16_IS_SINGLE ( c ) ) {
 * target ++ = c ;
 if ( offsets != NULL ) {
 * offsets ++ = - 1 ;
 }
 -- targetCapacity ;
 count = 0 ;
 c = 0 ;
 break ;
 }
 else if ( U16_IS_SURROGATE_LEAD ( c ) ) {
 c = 0 ;
 }
 else {
 break ;
 }
 }
 else if ( count == 4 ) {
 c = ( ( UChar ) p [ 0 ] << 8 ) | p [ 1 ] ;
 trail = ( ( UChar ) p [ 2 ] << 8 ) | p [ 3 ] ;
 if ( U16_IS_TRAIL ( trail ) ) {
 * target ++ = c ;
 if ( targetCapacity >= 2 ) {
 * target ++ = trail ;
 if ( offsets != NULL ) {
 * offsets ++ = - 1 ;
 * offsets ++ = - 1 ;
 }
 targetCapacity -= 2 ;
 }
 else {
 targetCapacity = 0 ;
 cnv -> UCharErrorBuffer [ 0 ] = trail ;
 cnv -> UCharErrorBufferLength = 1 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 count = 0 ;
 c = 0 ;
 break ;
 }
 else {
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 if ( ( ( const uint8_t * ) pArgs -> source - source ) >= 2 ) {
 source -= 2 ;
 }
 else {
 cnv -> toUnicodeStatus = 0x100 | p [ 2 ] ;
 -- source ;
 }
 cnv -> toULength = 2 ;
 pArgs -> source = ( const char * ) source ;
 pArgs -> target = target ;
 pArgs -> offsets = offsets ;
 return ;
 }
 }
 }
 while ( length > 0 ) ;
 cnv -> toULength = ( int8_t ) count ;
 }
 count = 2 * targetCapacity ;
 if ( count > length ) {
 count = length & ~ 1 ;
 }
 if ( c == 0 && count > 0 ) {
 length -= count ;
 count >>= 1 ;
 targetCapacity -= count ;
 if ( offsets == NULL ) {
 do {
 c = ( ( UChar ) source [ 0 ] << 8 ) | source [ 1 ] ;
 source += 2 ;
 if ( U16_IS_SINGLE ( c ) ) {
 * target ++ = c ;
 }
 else if ( U16_IS_SURROGATE_LEAD ( c ) && count >= 2 && U16_IS_TRAIL ( trail = ( ( UChar ) source [ 0 ] << 8 ) | source [ 1 ] ) ) {
 source += 2 ;
 -- count ;
 * target ++ = c ;
 * target ++ = trail ;
 }
 else {
 break ;
 }
 }
 while ( -- count > 0 ) ;
 }
 else {
 do {
 c = ( ( UChar ) source [ 0 ] << 8 ) | source [ 1 ] ;
 source += 2 ;
 if ( U16_IS_SINGLE ( c ) ) {
 * target ++ = c ;
 * offsets ++ = sourceIndex ;
 sourceIndex += 2 ;
 }
 else if ( U16_IS_SURROGATE_LEAD ( c ) && count >= 2 && U16_IS_TRAIL ( trail = ( ( UChar ) source [ 0 ] << 8 ) | source [ 1 ] ) ) {
 source += 2 ;
 -- count ;
 * target ++ = c ;
 * target ++ = trail ;
 * offsets ++ = sourceIndex ;
 * offsets ++ = sourceIndex ;
 sourceIndex += 4 ;
 }
 else {
 break ;
 }
 }
 while ( -- count > 0 ) ;
 }
 if ( count == 0 ) {
 c = 0 ;
 }
 else {
 length += 2 * ( count - 1 ) ;
 targetCapacity += count ;
 }
 }
 if ( c != 0 ) {
 cnv -> toUBytes [ 0 ] = ( uint8_t ) ( c >> 8 ) ;
 cnv -> toUBytes [ 1 ] = ( uint8_t ) c ;
 cnv -> toULength = 2 ;
 if ( U16_IS_SURROGATE_LEAD ( c ) ) {
 if ( length >= 2 ) {
 if ( U16_IS_TRAIL ( trail = ( ( UChar ) source [ 0 ] << 8 ) | source [ 1 ] ) ) {
 source += 2 ;
 length -= 2 ;
 * target ++ = c ;
 if ( offsets != NULL ) {
 * offsets ++ = sourceIndex ;
 }
 cnv -> UCharErrorBuffer [ 0 ] = trail ;
 cnv -> UCharErrorBufferLength = 1 ;
 cnv -> toULength = 0 ;
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
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
 }
 if ( U_SUCCESS ( * pErrorCode ) ) {
 if ( length > 0 ) {
 if ( targetCapacity == 0 ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 else {
 cnv -> toUBytes [ cnv -> toULength ++ ] = * source ++ ;
 }
 }
 }
 pArgs -> source = ( const char * ) source ;
 pArgs -> target = target ;
 pArgs -> offsets = offsets ;
 }