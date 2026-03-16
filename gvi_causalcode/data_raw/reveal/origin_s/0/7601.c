static UChar32 U_CALLCONV _UTF16LEGetNextUChar ( UConverterToUnicodeArgs * pArgs , UErrorCode * err ) {
 const uint8_t * s , * sourceLimit ;
 UChar32 c ;
 if ( pArgs -> converter -> mode < 8 ) {
 return UCNV_GET_NEXT_UCHAR_USE_TO_U ;
 }
 s = ( const uint8_t * ) pArgs -> source ;
 sourceLimit = ( const uint8_t * ) pArgs -> sourceLimit ;
 if ( s >= sourceLimit ) {
 * err = U_INDEX_OUTOFBOUNDS_ERROR ;
 return 0xffff ;
 }
 if ( s + 2 > sourceLimit ) {
 pArgs -> converter -> toUBytes [ 0 ] = * s ++ ;
 pArgs -> converter -> toULength = 1 ;
 pArgs -> source = ( const char * ) s ;
 * err = U_TRUNCATED_CHAR_FOUND ;
 return 0xffff ;
 }
 c = ( ( UChar32 ) s [ 1 ] << 8 ) | * s ;
 s += 2 ;
 if ( U_IS_SURROGATE ( c ) ) {
 if ( U16_IS_SURROGATE_LEAD ( c ) ) {
 if ( s + 2 <= sourceLimit ) {
 UChar trail ;
 trail = ( ( UChar ) s [ 1 ] << 8 ) | * s ;
 if ( U16_IS_TRAIL ( trail ) ) {
 c = U16_GET_SUPPLEMENTARY ( c , trail ) ;
 s += 2 ;
 }
 else {
 c = - 2 ;
 }
 }
 else {
 uint8_t * bytes = pArgs -> converter -> toUBytes ;
 s -= 2 ;
 pArgs -> converter -> toULength = ( int8_t ) ( sourceLimit - s ) ;
 do {
 * bytes ++ = * s ++ ;
 }
 while ( s < sourceLimit ) ;
 c = 0xffff ;
 * err = U_TRUNCATED_CHAR_FOUND ;
 }
 }
 else {
 c = - 2 ;
 }
 if ( c < 0 ) {
 uint8_t * bytes = pArgs -> converter -> toUBytes ;
 pArgs -> converter -> toULength = 2 ;
 * bytes = * ( s - 2 ) ;
 bytes [ 1 ] = * ( s - 1 ) ;
 c = 0xffff ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 }
 }
 pArgs -> source = ( const char * ) s ;
 return c ;
 }