static void ucnv_Latin1FromUTF8 ( UConverterFromUnicodeArgs * pFromUArgs , UConverterToUnicodeArgs * pToUArgs , UErrorCode * pErrorCode ) {
 UConverter * utf8 ;
 const uint8_t * source , * sourceLimit ;
 uint8_t * target ;
 int32_t targetCapacity ;
 UChar32 c ;
 uint8_t b , t1 ;
 utf8 = pToUArgs -> converter ;
 source = ( uint8_t * ) pToUArgs -> source ;
 sourceLimit = ( uint8_t * ) pToUArgs -> sourceLimit ;
 target = ( uint8_t * ) pFromUArgs -> target ;
 targetCapacity = ( int32_t ) ( pFromUArgs -> targetLimit - pFromUArgs -> target ) ;
 c = ( UChar32 ) utf8 -> toUnicodeStatus ;
 if ( c != 0 && source < sourceLimit ) {
 if ( targetCapacity == 0 ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 return ;
 }
 else if ( c >= 0xc2 && c <= 0xc3 && ( t1 = ( uint8_t ) ( * source - 0x80 ) ) <= 0x3f ) {
 ++ source ;
 * target ++ = ( uint8_t ) ( ( ( c & 3 ) << 6 ) | t1 ) ;
 -- targetCapacity ;
 utf8 -> toUnicodeStatus = 0 ;
 utf8 -> toULength = 0 ;
 }
 else {
 * pErrorCode = U_USING_DEFAULT_WARNING ;
 return ;
 }
 }
 if ( source < sourceLimit && U8_IS_LEAD ( * ( sourceLimit - 1 ) ) ) {
 -- sourceLimit ;
 }
 while ( source < sourceLimit ) {
 if ( targetCapacity > 0 ) {
 b = * source ++ ;
 if ( ( int8_t ) b >= 0 ) {
 * target ++ = ( uint8_t ) b ;
 -- targetCapacity ;
 }
 else if ( b >= 0xc2 && b <= 0xc3 && ( t1 = ( uint8_t ) ( * source - 0x80 ) ) <= 0x3f ) {
 ++ source ;
 * target ++ = ( uint8_t ) ( ( ( b & 3 ) << 6 ) | t1 ) ;
 -- targetCapacity ;
 }
 else {
 pToUArgs -> source = ( char * ) ( source - 1 ) ;
 pFromUArgs -> target = ( char * ) target ;
 * pErrorCode = U_USING_DEFAULT_WARNING ;
 return ;
 }
 }
 else {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 if ( U_SUCCESS ( * pErrorCode ) && source < ( sourceLimit = ( uint8_t * ) pToUArgs -> sourceLimit ) ) {
 utf8 -> toUnicodeStatus = utf8 -> toUBytes [ 0 ] = b = * source ++ ;
 utf8 -> toULength = 1 ;
 utf8 -> mode = U8_COUNT_TRAIL_BYTES ( b ) + 1 ;
 }
 pToUArgs -> source = ( char * ) source ;
 pFromUArgs -> target = ( char * ) target ;
 }