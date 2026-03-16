static void ucnv_ASCIIFromUTF8 ( UConverterFromUnicodeArgs * pFromUArgs , UConverterToUnicodeArgs * pToUArgs , UErrorCode * pErrorCode ) {
 const uint8_t * source , * sourceLimit ;
 uint8_t * target ;
 int32_t targetCapacity , length ;
 uint8_t c ;
 if ( pToUArgs -> converter -> toUnicodeStatus != 0 ) {
 * pErrorCode = U_USING_DEFAULT_WARNING ;
 return ;
 }
 source = ( const uint8_t * ) pToUArgs -> source ;
 sourceLimit = ( const uint8_t * ) pToUArgs -> sourceLimit ;
 target = ( uint8_t * ) pFromUArgs -> target ;
 targetCapacity = ( int32_t ) ( pFromUArgs -> targetLimit - pFromUArgs -> target ) ;
 length = ( int32_t ) ( sourceLimit - source ) ;
 if ( length < targetCapacity ) {
 targetCapacity = length ;
 }
 if ( targetCapacity >= 16 ) {
 int32_t count , loops ;
 uint8_t oredChars ;
 loops = count = targetCapacity >> 4 ;
 do {
 oredChars = * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 oredChars |= * target ++ = * source ++ ;
 if ( oredChars > 0x7f ) {
 source -= 16 ;
 target -= 16 ;
 break ;
 }
 }
 while ( -- count > 0 ) ;
 count = loops - count ;
 targetCapacity -= 16 * count ;
 }
 c = 0 ;
 while ( targetCapacity > 0 && ( c = * source ) <= 0x7f ) {
 ++ source ;
 * target ++ = c ;
 -- targetCapacity ;
 }
 if ( c > 0x7f ) {
 * pErrorCode = U_USING_DEFAULT_WARNING ;
 }
 else if ( source < sourceLimit && target >= ( const uint8_t * ) pFromUArgs -> targetLimit ) {
 * pErrorCode = U_BUFFER_OVERFLOW_ERROR ;
 }
 pToUArgs -> source = ( const char * ) source ;
 pFromUArgs -> target = ( char * ) target ;
 }