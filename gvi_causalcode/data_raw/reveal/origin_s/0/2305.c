static UChar32 U_CALLCONV T_UConverter_getNextUChar_UTF32_BE ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 const uint8_t * mySource ;
 UChar32 myUChar ;
 int32_t length ;
 mySource = ( const uint8_t * ) args -> source ;
 if ( mySource >= ( const uint8_t * ) args -> sourceLimit ) {
 * err = U_INDEX_OUTOFBOUNDS_ERROR ;
 return 0xffff ;
 }
 length = ( int32_t ) ( ( const uint8_t * ) args -> sourceLimit - mySource ) ;
 if ( length < 4 ) {
 uprv_memcpy ( args -> converter -> toUBytes , mySource , length ) ;
 args -> converter -> toULength = ( int8_t ) length ;
 args -> source = ( const char * ) ( mySource + length ) ;
 * err = U_TRUNCATED_CHAR_FOUND ;
 return 0xffff ;
 }
 myUChar = ( ( UChar32 ) mySource [ 0 ] << 24 ) | ( ( UChar32 ) mySource [ 1 ] << 16 ) | ( ( UChar32 ) mySource [ 2 ] << 8 ) | ( ( UChar32 ) mySource [ 3 ] ) ;
 args -> source = ( const char * ) ( mySource + 4 ) ;
 if ( ( uint32_t ) myUChar <= MAXIMUM_UTF && ! U_IS_SURROGATE ( myUChar ) ) {
 return myUChar ;
 }
 uprv_memcpy ( args -> converter -> toUBytes , mySource , 4 ) ;
 args -> converter -> toULength = 4 ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 return 0xffff ;
 }