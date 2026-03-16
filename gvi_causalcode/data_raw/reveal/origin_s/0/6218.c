static void U_CALLCONV T_UConverter_toUnicode_UTF32_BE_OFFSET_LOGIC ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 const unsigned char * mySource = ( unsigned char * ) args -> source ;
 UChar * myTarget = args -> target ;
 int32_t * myOffsets = args -> offsets ;
 const unsigned char * sourceLimit = ( unsigned char * ) args -> sourceLimit ;
 const UChar * targetLimit = args -> targetLimit ;
 unsigned char * toUBytes = args -> converter -> toUBytes ;
 uint32_t ch , i ;
 int32_t offsetNum = 0 ;
 if ( args -> converter -> toUnicodeStatus && myTarget < targetLimit ) {
 i = args -> converter -> toULength ;
 args -> converter -> toULength = 0 ;
 ch = args -> converter -> toUnicodeStatus - 1 ;
 args -> converter -> toUnicodeStatus = 0 ;
 goto morebytes ;
 }
 while ( mySource < sourceLimit && myTarget < targetLimit ) {
 i = 0 ;
 ch = 0 ;
 morebytes : while ( i < sizeof ( uint32_t ) ) {
 if ( mySource < sourceLimit ) {
 ch = ( ch << 8 ) | ( uint8_t ) ( * mySource ) ;
 toUBytes [ i ++ ] = ( char ) * ( mySource ++ ) ;
 }
 else {
 args -> converter -> toUnicodeStatus = ch + 1 ;
 args -> converter -> toULength = ( int8_t ) i ;
 goto donefornow ;
 }
 }
 if ( ch <= MAXIMUM_UTF && ! U_IS_SURROGATE ( ch ) ) {
 if ( ch <= MAXIMUM_UCS2 ) {
 * ( myTarget ++ ) = ( UChar ) ch ;
 * ( myOffsets ++ ) = offsetNum ;
 }
 else {
 * ( myTarget ++ ) = U16_LEAD ( ch ) ;
 * myOffsets ++ = offsetNum ;
 ch = U16_TRAIL ( ch ) ;
 if ( myTarget < targetLimit ) {
 * ( myTarget ++ ) = ( UChar ) ch ;
 * ( myOffsets ++ ) = offsetNum ;
 }
 else {
 args -> converter -> UCharErrorBuffer [ 0 ] = ( UChar ) ch ;
 args -> converter -> UCharErrorBufferLength = 1 ;
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 }
 else {
 args -> converter -> toULength = ( int8_t ) i ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 offsetNum += i ;
 }
 donefornow : if ( mySource < sourceLimit && myTarget >= targetLimit && U_SUCCESS ( * err ) ) {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 args -> target = myTarget ;
 args -> source = ( const char * ) mySource ;
 args -> offsets = myOffsets ;
 }