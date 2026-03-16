static UChar32 U_CALLCONV _ASCIIGetNextUChar ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 const uint8_t * source ;
 uint8_t b ;
 source = ( const uint8_t * ) pArgs -> source ;
 if ( source < ( const uint8_t * ) pArgs -> sourceLimit ) {
 b = * source ++ ;
 pArgs -> source = ( const char * ) source ;
 if ( b <= 0x7f ) {
 return b ;
 }
 else {
 UConverter * cnv = pArgs -> converter ;
 cnv -> toUBytes [ 0 ] = b ;
 cnv -> toULength = 1 ;
 * pErrorCode = U_ILLEGAL_CHAR_FOUND ;
 return 0xffff ;
 }
 }
 * pErrorCode = U_INDEX_OUTOFBOUNDS_ERROR ;
 return 0xffff ;
 }