static void U_CALLCONV UConverter_fromUnicode_HZ_OFFSETS_LOGIC ( UConverterFromUnicodeArgs * args , UErrorCode * err ) {
 const UChar * mySource = args -> source ;
 char * myTarget = args -> target ;
 int32_t * offsets = args -> offsets ;
 int32_t mySourceIndex = 0 ;
 int32_t myTargetIndex = 0 ;
 int32_t targetLength = ( int32_t ) ( args -> targetLimit - myTarget ) ;
 int32_t mySourceLength = ( int32_t ) ( args -> sourceLimit - args -> source ) ;
 uint32_t targetUniChar = 0x0000 ;
 UChar32 mySourceChar = 0x0000 ;
 UConverterDataHZ * myConverterData = ( UConverterDataHZ * ) args -> converter -> extraInfo ;
 UBool isTargetUCharDBCS = ( UBool ) myConverterData -> isTargetUCharDBCS ;
 UBool oldIsTargetUCharDBCS ;
 int len = 0 ;
 const char * escSeq = NULL ;
 if ( args -> converter -> fromUChar32 != 0 && myTargetIndex < targetLength ) {
 goto getTrail ;
 }
 while ( mySourceIndex < mySourceLength ) {
 targetUniChar = missingCharMarker ;
 if ( myTargetIndex < targetLength ) {
 mySourceChar = ( UChar ) mySource [ mySourceIndex ++ ] ;
 oldIsTargetUCharDBCS = isTargetUCharDBCS ;
 if ( mySourceChar == UCNV_TILDE ) {
 len = ESC_LEN ;
 escSeq = TILDE_ESCAPE ;
 CONCAT_ESCAPE_MACRO ( args , myTargetIndex , targetLength , escSeq , err , len , mySourceIndex ) ;
 continue ;
 }
 else if ( mySourceChar <= 0x7f ) {
 targetUniChar = mySourceChar ;
 }
 else {
 int32_t length = ucnv_MBCSFromUChar32 ( myConverterData -> gbConverter -> sharedData , mySourceChar , & targetUniChar , args -> converter -> useFallback ) ;
 if ( length == 2 && ( uint16_t ) ( targetUniChar - 0xa1a1 ) <= ( 0xfdfe - 0xa1a1 ) && ( uint8_t ) ( targetUniChar - 0xa1 ) <= ( 0xfe - 0xa1 ) ) {
 targetUniChar -= 0x8080 ;
 }
 else {
 targetUniChar = missingCharMarker ;
 }
 }
 if ( targetUniChar != missingCharMarker ) {
 myConverterData -> isTargetUCharDBCS = isTargetUCharDBCS = ( UBool ) ( targetUniChar > 0x00FF ) ;
 if ( oldIsTargetUCharDBCS != isTargetUCharDBCS || ! myConverterData -> isEscapeAppended ) {
 if ( ! isTargetUCharDBCS ) {
 len = ESC_LEN ;
 escSeq = SB_ESCAPE ;
 CONCAT_ESCAPE_MACRO ( args , myTargetIndex , targetLength , escSeq , err , len , mySourceIndex ) ;
 myConverterData -> isEscapeAppended = TRUE ;
 }
 else {
 len = ESC_LEN ;
 escSeq = DB_ESCAPE ;
 CONCAT_ESCAPE_MACRO ( args , myTargetIndex , targetLength , escSeq , err , len , mySourceIndex ) ;
 myConverterData -> isEscapeAppended = TRUE ;
 }
 }
 if ( isTargetUCharDBCS ) {
 if ( myTargetIndex < targetLength ) {
 myTarget [ myTargetIndex ++ ] = ( char ) ( targetUniChar >> 8 ) ;
 if ( offsets ) {
 * ( offsets ++ ) = mySourceIndex - 1 ;
 }
 if ( myTargetIndex < targetLength ) {
 myTarget [ myTargetIndex ++ ] = ( char ) targetUniChar ;
 if ( offsets ) {
 * ( offsets ++ ) = mySourceIndex - 1 ;
 }
 }
 else {
 args -> converter -> charErrorBuffer [ args -> converter -> charErrorBufferLength ++ ] = ( char ) targetUniChar ;
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 else {
 args -> converter -> charErrorBuffer [ args -> converter -> charErrorBufferLength ++ ] = ( char ) ( targetUniChar >> 8 ) ;
 args -> converter -> charErrorBuffer [ args -> converter -> charErrorBufferLength ++ ] = ( char ) targetUniChar ;
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 else {
 if ( myTargetIndex < targetLength ) {
 myTarget [ myTargetIndex ++ ] = ( char ) ( targetUniChar ) ;
 if ( offsets ) {
 * ( offsets ++ ) = mySourceIndex - 1 ;
 }
 }
 else {
 args -> converter -> charErrorBuffer [ args -> converter -> charErrorBufferLength ++ ] = ( char ) targetUniChar ;
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 }
 }
 else {
 if ( U16_IS_SURROGATE ( mySourceChar ) ) {
 if ( U16_IS_SURROGATE_LEAD ( mySourceChar ) ) {
 args -> converter -> fromUChar32 = mySourceChar ;
 getTrail : if ( mySourceIndex < mySourceLength ) {
 UChar trail = ( UChar ) args -> source [ mySourceIndex ] ;
 if ( U16_IS_TRAIL ( trail ) ) {
 ++ mySourceIndex ;
 mySourceChar = U16_GET_SUPPLEMENTARY ( args -> converter -> fromUChar32 , trail ) ;
 args -> converter -> fromUChar32 = 0x00 ;
 * err = U_INVALID_CHAR_FOUND ;
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 }
 }
 else {
 * err = U_ZERO_ERROR ;
 }
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 }
 }
 else {
 * err = U_INVALID_CHAR_FOUND ;
 }
 args -> converter -> fromUChar32 = mySourceChar ;
 break ;
 }
 }
 else {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 targetUniChar = missingCharMarker ;
 }
 args -> target += myTargetIndex ;
 args -> source += mySourceIndex ;
 myConverterData -> isTargetUCharDBCS = isTargetUCharDBCS ;
 }