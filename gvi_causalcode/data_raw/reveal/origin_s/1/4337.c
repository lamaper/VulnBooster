static void T_UConverter_fromUnicode_UTF32_BE_OFFSET_LOGIC ( UConverterFromUnicodeArgs * args , UErrorCode * err ) {
 const UChar * mySource = args -> source ;
 unsigned char * myTarget ;
 int32_t * myOffsets ;
 const UChar * sourceLimit = args -> sourceLimit ;
 const unsigned char * targetLimit = ( unsigned char * ) args -> targetLimit ;
 UChar32 ch , ch2 ;
 int32_t offsetNum = 0 ;
 unsigned int indexToWrite ;
 unsigned char temp [ sizeof ( uint32_t ) ] ;
 if ( mySource >= sourceLimit ) {
 return ;
 }
 if ( args -> converter -> fromUnicodeStatus == UCNV_NEED_TO_WRITE_BOM ) {
 static const char bom [ ] = {
 0 , 0 , ( char ) 0xfe , ( char ) 0xff }
 ;
 ucnv_fromUWriteBytes ( args -> converter , bom , 4 , & args -> target , args -> targetLimit , & args -> offsets , - 1 , err ) ;
 args -> converter -> fromUnicodeStatus = 0 ;
 }
 myTarget = ( unsigned char * ) args -> target ;
 myOffsets = args -> offsets ;
 temp [ 0 ] = 0 ;
 if ( args -> converter -> fromUChar32 ) {
 ch = args -> converter -> fromUChar32 ;
 args -> converter -> fromUChar32 = 0 ;
 goto lowsurogate ;
 }
 while ( mySource < sourceLimit && myTarget < targetLimit ) {
 ch = * ( mySource ++ ) ;
 if ( U_IS_SURROGATE ( ch ) ) {
 if ( U_IS_LEAD ( ch ) ) {
 lowsurogate : if ( mySource < sourceLimit ) {
 ch2 = * mySource ;
 if ( U_IS_TRAIL ( ch2 ) ) {
 ch = ( ( ch - SURROGATE_HIGH_START ) << HALF_SHIFT ) + ch2 + SURROGATE_LOW_BASE ;
 mySource ++ ;
 }
 else {
 args -> converter -> fromUChar32 = ch ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 }
 else {
 args -> converter -> fromUChar32 = ch ;
 if ( args -> flush ) {
 * err = U_ILLEGAL_CHAR_FOUND ;
 }
 break ;
 }
 }
 else {
 args -> converter -> fromUChar32 = ch ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 }
 temp [ 1 ] = ( uint8_t ) ( ch >> 16 & 0x1F ) ;
 temp [ 2 ] = ( uint8_t ) ( ch >> 8 ) ;
 temp [ 3 ] = ( uint8_t ) ( ch ) ;
 for ( indexToWrite = 0 ;
 indexToWrite <= sizeof ( uint32_t ) - 1 ;
 indexToWrite ++ ) {
 if ( myTarget < targetLimit ) {
 * ( myTarget ++ ) = temp [ indexToWrite ] ;
 * ( myOffsets ++ ) = offsetNum ;
 }
 else {
 args -> converter -> charErrorBuffer [ args -> converter -> charErrorBufferLength ++ ] = temp [ indexToWrite ] ;
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 offsetNum = offsetNum + 1 + ( temp [ 1 ] != 0 ) ;
 }
 if ( mySource < sourceLimit && myTarget >= targetLimit && U_SUCCESS ( * err ) ) {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 args -> target = ( char * ) myTarget ;
 args -> source = mySource ;
 args -> offsets = myOffsets ;
 }