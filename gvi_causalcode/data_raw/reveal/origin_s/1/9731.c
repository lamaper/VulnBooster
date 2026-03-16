static void ucnv_UTF8FromUTF8 ( UConverterFromUnicodeArgs * pFromUArgs , UConverterToUnicodeArgs * pToUArgs , UErrorCode * pErrorCode ) {
 UConverter * utf8 ;
 const uint8_t * source , * sourceLimit ;
 uint8_t * target ;
 int32_t targetCapacity ;
 int32_t count ;
 int8_t oldToULength , toULength , toULimit ;
 UChar32 c ;
 uint8_t b , t1 , t2 ;
 utf8 = pToUArgs -> converter ;
 source = ( uint8_t * ) pToUArgs -> source ;
 sourceLimit = ( uint8_t * ) pToUArgs -> sourceLimit ;
 target = ( uint8_t * ) pFromUArgs -> target ;
 targetCapacity = ( int32_t ) ( pFromUArgs -> targetLimit - pFromUArgs -> target ) ;
 c = ( UChar32 ) utf8 -> toUnicodeStatus ;
 if ( c != 0 ) {
 toULength = oldToULength = utf8 -> toULength ;
 toULimit = ( int8_t ) utf8 -> mode ;
 }
 else {
 toULength = oldToULength = toULimit = 0 ;
 }
 count = ( int32_t ) ( sourceLimit - source ) + oldToULength ;
 if ( count < toULimit ) {
 }
 else if ( targetCapacity < toULimit ) {
 * pErrorCode = U_USING_DEFAULT_WARNING ;
 return ;
 }
 else {
 int32_t i ;
 if ( count > targetCapacity ) {
 count = targetCapacity ;
 }
 i = 0 ;
 while ( i < 3 && i < ( count - toULimit ) ) {
 b = source [ count - oldToULength - i - 1 ] ;
 if ( U8_IS_TRAIL ( b ) ) {
 ++ i ;
 }
 else {
 if ( i < U8_COUNT_TRAIL_BYTES ( b ) ) {
 count -= i + 1 ;
 }
 break ;
 }
 }
 }
 if ( c != 0 ) {
 utf8 -> toUnicodeStatus = 0 ;
 utf8 -> toULength = 0 ;
 goto moreBytes ;
 }
 while ( count > 0 ) {
 b = * source ++ ;
 if ( ( int8_t ) b >= 0 ) {
 * target ++ = b ;
 -- count ;
 continue ;
 }
 else {
 if ( b > 0xe0 ) {
 if ( ( t1 = source [ 0 ] ) >= 0x80 && ( ( b < 0xed && ( t1 <= 0xbf ) ) || ( b == 0xed && ( t1 <= 0x9f ) ) ) && ( t2 = source [ 1 ] ) >= 0x80 && t2 <= 0xbf ) {
 source += 2 ;
 * target ++ = b ;
 * target ++ = t1 ;
 * target ++ = t2 ;
 count -= 3 ;
 continue ;
 }
 }
 else if ( b < 0xe0 ) {
 if ( b >= 0xc2 && ( t1 = * source ) >= 0x80 && t1 <= 0xbf ) {
 ++ source ;
 * target ++ = b ;
 * target ++ = t1 ;
 count -= 2 ;
 continue ;
 }
 }
 else if ( b == 0xe0 ) {
 if ( ( t1 = source [ 0 ] ) >= 0xa0 && t1 <= 0xbf && ( t2 = source [ 1 ] ) >= 0x80 && t2 <= 0xbf ) {
 source += 2 ;
 * target ++ = b ;
 * target ++ = t1 ;
 * target ++ = t2 ;
 count -= 3 ;
 continue ;
 }
 }
 oldToULength = 0 ;
 toULength = 1 ;
 toULimit = U8_COUNT_TRAIL_BYTES ( b ) + 1 ;
 c = b ;
 moreBytes : while ( toULength < toULimit ) {
 if ( source < sourceLimit ) {
 b = * source ;
 if ( U8_IS_TRAIL ( b ) ) {
 ++ source ;
 ++ toULength ;
 c = ( c << 6 ) + b ;
 }
 else {
 break ;
 }
 }
 else {
 source -= ( toULength - oldToULength ) ;
 while ( oldToULength < toULength ) {
 utf8 -> toUBytes [ oldToULength ++ ] = * source ++ ;
 }
 utf8 -> toUnicodeStatus = c ;
 utf8 -> toULength = toULength ;
 utf8 -> mode = toULimit ;
 pToUArgs -> source = ( char * ) source ;
 pFromUArgs -> target = ( char * ) target ;
 return ;
 }
 }
 if ( toULength == toULimit && ( toULength == 3 || toULength == 2 ) && ( c -= utf8_offsets [ toULength ] ) >= utf8_minLegal [ toULength ] && ( c <= 0xd7ff || 0xe000 <= c ) ) {
 }
 else if ( toULength == toULimit && toULength == 4 && ( 0x10000 <= ( c -= utf8_offsets [ 4 ] ) && c <= 0x10ffff ) ) {
 }
 else {
 source -= ( toULength - oldToULength ) ;
 while ( oldToULength < toULength ) {
 utf8 -> toUBytes [ oldToULength ++ ] = * source ++ ;
 }
 utf8 -> toULength = toULength ;
 pToUArgs -> source = ( char * ) source ;
 pFromUArgs -> target = ( char * ) target ;
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 return ;
 }
 {
 int8_t i ;
 for ( i = 0 ;
 i < oldToULength ;
 ++ i ) {
 * target ++ = utf8 -> toUBytes [ i ] ;
 }
 source -= ( toULength - oldToULength ) ;
 for ( ;
 i < toULength ;
 ++ i ) {
 * target ++ = * source ++ ;
 }
 count -= toULength ;
 }
 }
 }
 if ( U_SUCCESS ( * pErrorCode ) && source < sourceLimit ) {
 if ( target == ( const uint8_t * ) pFromUArgs -> targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 else {
 b = * source ;
 toULimit = U8_COUNT_TRAIL_BYTES ( b ) + 1 ;
 if ( toULimit > ( sourceLimit - source ) ) {
 toULength = 0 ;
 c = b ;
 for ( ;
 ;
 ) {
 utf8 -> toUBytes [ toULength ++ ] = b ;
 if ( ++ source == sourceLimit ) {
 utf8 -> toUnicodeStatus = c ;
 utf8 -> toULength = toULength ;
 utf8 -> mode = toULimit ;
 break ;
 }
 else if ( ! U8_IS_TRAIL ( b = * source ) ) {
 utf8 -> toULength = toULength ;
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 c = ( c << 6 ) + b ;
 }
 }
 else {
 * pErrorCode = U_USING_DEFAULT_WARNING ;
 }
 }
 }
 pToUArgs -> source = ( char * ) source ;
 pFromUArgs -> target = ( char * ) target ;
 }