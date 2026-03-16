static void U_CALLCONV UConverter_toUnicode_HZ_OFFSETS_LOGIC ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 char tempBuf [ 2 ] ;
 const char * mySource = ( char * ) args -> source ;
 UChar * myTarget = args -> target ;
 const char * mySourceLimit = args -> sourceLimit ;
 UChar32 targetUniChar = 0x0000 ;
 int32_t mySourceChar = 0x0000 ;
 UConverterDataHZ * myData = ( UConverterDataHZ * ) ( args -> converter -> extraInfo ) ;
 tempBuf [ 0 ] = 0 ;
 tempBuf [ 1 ] = 0 ;
 while ( mySource < mySourceLimit ) {
 if ( myTarget < args -> targetLimit ) {
 mySourceChar = ( unsigned char ) * mySource ++ ;
 if ( args -> converter -> mode == UCNV_TILDE ) {
 args -> converter -> mode = 0 ;
 switch ( mySourceChar ) {
 case 0x0A : continue ;
 case UCNV_TILDE : if ( args -> offsets ) {
 args -> offsets [ myTarget - args -> target ] = ( int32_t ) ( mySource - args -> source - 2 ) ;
 }
 * ( myTarget ++ ) = ( UChar ) mySourceChar ;
 myData -> isEmptySegment = FALSE ;
 continue ;
 case UCNV_OPEN_BRACE : case UCNV_CLOSE_BRACE : myData -> isStateDBCS = ( mySourceChar == UCNV_OPEN_BRACE ) ;
 if ( myData -> isEmptySegment ) {
 myData -> isEmptySegment = FALSE ;
 * err = U_ILLEGAL_ESCAPE_SEQUENCE ;
 args -> converter -> toUCallbackReason = UCNV_IRREGULAR ;
 args -> converter -> toUBytes [ 0 ] = UCNV_TILDE ;
 args -> converter -> toUBytes [ 1 ] = mySourceChar ;
 args -> converter -> toULength = 2 ;
 args -> target = myTarget ;
 args -> source = mySource ;
 return ;
 }
 myData -> isEmptySegment = TRUE ;
 continue ;
 default : myData -> isEmptySegment = FALSE ;
 * err = U_ILLEGAL_ESCAPE_SEQUENCE ;
 args -> converter -> toUBytes [ 0 ] = UCNV_TILDE ;
 if ( myData -> isStateDBCS ? ( 0x21 <= mySourceChar && mySourceChar <= 0x7e ) : mySourceChar <= 0x7f ) {
 args -> converter -> toULength = 1 ;
 -- mySource ;
 }
 else {
 args -> converter -> toUBytes [ 1 ] = mySourceChar ;
 args -> converter -> toULength = 2 ;
 }
 args -> target = myTarget ;
 args -> source = mySource ;
 return ;
 }
 }
 else if ( myData -> isStateDBCS ) {
 if ( args -> converter -> toUnicodeStatus == 0x00 ) {
 if ( mySourceChar == UCNV_TILDE ) {
 args -> converter -> mode = UCNV_TILDE ;
 }
 else {
 args -> converter -> toUnicodeStatus = ( uint32_t ) ( mySourceChar | 0x100 ) ;
 myData -> isEmptySegment = FALSE ;
 }
 continue ;
 }
 else {
 int leadIsOk , trailIsOk ;
 uint32_t leadByte = args -> converter -> toUnicodeStatus & 0xff ;
 targetUniChar = 0xffff ;
 leadIsOk = ( uint8_t ) ( leadByte - 0x21 ) <= ( 0x7d - 0x21 ) ;
 trailIsOk = ( uint8_t ) ( mySourceChar - 0x21 ) <= ( 0x7e - 0x21 ) ;
 if ( leadIsOk && trailIsOk ) {
 tempBuf [ 0 ] = ( char ) ( leadByte + 0x80 ) ;
 tempBuf [ 1 ] = ( char ) ( mySourceChar + 0x80 ) ;
 targetUniChar = ucnv_MBCSSimpleGetNextUChar ( myData -> gbConverter -> sharedData , tempBuf , 2 , args -> converter -> useFallback ) ;
 mySourceChar = ( leadByte << 8 ) | mySourceChar ;
 }
 else if ( trailIsOk ) {
 -- mySource ;
 mySourceChar = ( int32_t ) leadByte ;
 }
 else {
 mySourceChar = 0x10000 | ( leadByte << 8 ) | mySourceChar ;
 }
 args -> converter -> toUnicodeStatus = 0x00 ;
 }
 }
 else {
 if ( mySourceChar == UCNV_TILDE ) {
 args -> converter -> mode = UCNV_TILDE ;
 continue ;
 }
 else if ( mySourceChar <= 0x7f ) {
 targetUniChar = ( UChar ) mySourceChar ;
 myData -> isEmptySegment = FALSE ;
 }
 else {
 targetUniChar = 0xffff ;
 myData -> isEmptySegment = FALSE ;
 }
 }
 if ( targetUniChar < 0xfffe ) {
 if ( args -> offsets ) {
 args -> offsets [ myTarget - args -> target ] = ( int32_t ) ( mySource - args -> source - 1 - ( myData -> isStateDBCS ) ) ;
 }
 * ( myTarget ++ ) = ( UChar ) targetUniChar ;
 }
 else {
 if ( targetUniChar == 0xfffe ) {
 * err = U_INVALID_CHAR_FOUND ;
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 }
 if ( mySourceChar > 0xff ) {
 args -> converter -> toUBytes [ 0 ] = ( uint8_t ) ( mySourceChar >> 8 ) ;
 args -> converter -> toUBytes [ 1 ] = ( uint8_t ) mySourceChar ;
 args -> converter -> toULength = 2 ;
 }
 else {
 args -> converter -> toUBytes [ 0 ] = ( uint8_t ) mySourceChar ;
 args -> converter -> toULength = 1 ;
 }
 break ;
 }
 }
 else {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 args -> target = myTarget ;
 args -> source = mySource ;
 }