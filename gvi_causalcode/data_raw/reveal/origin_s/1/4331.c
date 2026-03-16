static UChar32 _Latin1GetNextUChar ( UConverterToUnicodeArgs * pArgs , UErrorCode * pErrorCode ) {
 const uint8_t * source = ( const uint8_t * ) pArgs -> source ;
 if ( source < ( const uint8_t * ) pArgs -> sourceLimit ) {
 pArgs -> source = ( const char * ) ( source + 1 ) ;
 return * source ;
 }
 * pErrorCode = U_INDEX_OUTOFBOUNDS_ERROR ;
 return 0xffff ;
 }