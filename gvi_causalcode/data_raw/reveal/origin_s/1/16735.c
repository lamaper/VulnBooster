static void UConverter_fromUnicode_ISCII_OFFSETS_LOGIC ( UConverterFromUnicodeArgs * args , UErrorCode * err ) {
 const UChar * source = args -> source ;
 const UChar * sourceLimit = args -> sourceLimit ;
 unsigned char * target = ( unsigned char * ) args -> target ;
 unsigned char * targetLimit = ( unsigned char * ) args -> targetLimit ;
 int32_t * offsets = args -> offsets ;
 uint32_t targetByteUnit = 0x0000 ;
 UChar32 sourceChar = 0x0000 ;
 UChar32 tempContextFromUnicode = 0x0000 ;
 UConverterDataISCII * converterData ;
 uint16_t newDelta = 0 ;
 uint16_t range = 0 ;
 UBool deltaChanged = FALSE ;
 if ( ( args -> converter == NULL ) || ( args -> targetLimit < args -> target ) || ( args -> sourceLimit < args -> source ) ) {
 * err = U_ILLEGAL_ARGUMENT_ERROR ;
 return ;
 }
 converterData = ( UConverterDataISCII * ) args -> converter -> extraInfo ;
 newDelta = converterData -> currentDeltaFromUnicode ;
 range = ( uint16_t ) ( newDelta / DELTA ) ;
 if ( ( sourceChar = args -> converter -> fromUChar32 ) != 0 ) {
 goto getTrail ;
 }
 while ( source < sourceLimit ) {
 if ( args -> converter -> fromUnicodeStatus == LF ) {
 targetByteUnit = ATR << 8 ;
 targetByteUnit += ( uint8_t ) lookupInitialData [ range ] . isciiLang ;
 args -> converter -> fromUnicodeStatus = 0x0000 ;
 WRITE_TO_TARGET_FROM_U ( args , offsets , source , target , targetLimit , targetByteUnit , err ) ;
 if ( U_FAILURE ( * err ) ) {
 break ;
 }
 }
 sourceChar = * source ++ ;
 tempContextFromUnicode = converterData -> contextCharFromUnicode ;
 targetByteUnit = missingCharMarker ;
 if ( sourceChar <= ASCII_END ) {
 args -> converter -> fromUnicodeStatus = sourceChar ;
 WRITE_TO_TARGET_FROM_U ( args , offsets , source , target , targetLimit , sourceChar , err ) ;
 if ( U_FAILURE ( * err ) ) {
 break ;
 }
 continue ;
 }
 switch ( sourceChar ) {
 case ZWNJ : if ( converterData -> contextCharFromUnicode ) {
 converterData -> contextCharFromUnicode = 0x00 ;
 targetByteUnit = ISCII_HALANT ;
 }
 else {
 converterData -> contextCharFromUnicode = 0x00 ;
 continue ;
 }
 break ;
 case ZWJ : if ( converterData -> contextCharFromUnicode ) {
 targetByteUnit = ISCII_NUKTA ;
 }
 else {
 targetByteUnit = ISCII_INV ;
 }
 converterData -> contextCharFromUnicode = 0x00 ;
 break ;
 default : if ( ( uint16_t ) ( INDIC_BLOCK_END - sourceChar ) <= INDIC_RANGE ) {
 if ( sourceChar != DANDA && sourceChar != DOUBLE_DANDA ) {
 range = ( uint16_t ) ( ( sourceChar - INDIC_BLOCK_BEGIN ) / DELTA ) ;
 newDelta = ( uint16_t ) ( range * DELTA ) ;
 if ( newDelta != converterData -> currentDeltaFromUnicode || converterData -> isFirstBuffer ) {
 converterData -> currentDeltaFromUnicode = newDelta ;
 converterData -> currentMaskFromUnicode = lookupInitialData [ range ] . maskEnum ;
 deltaChanged = TRUE ;
 converterData -> isFirstBuffer = FALSE ;
 }
 if ( converterData -> currentDeltaFromUnicode == PNJ_DELTA ) {
 if ( sourceChar == PNJ_TIPPI ) {
 sourceChar = PNJ_BINDI ;
 }
 else if ( sourceChar == PNJ_ADHAK ) {
 converterData -> contextCharFromUnicode = PNJ_ADHAK ;
 }
 }
 sourceChar -= converterData -> currentDeltaFromUnicode ;
 }
 targetByteUnit = fromUnicodeTable [ ( uint8_t ) sourceChar ] ;
 if ( ( validityTable [ ( uint8_t ) sourceChar ] & converterData -> currentMaskFromUnicode ) == 0 ) {
 if ( converterData -> currentDeltaFromUnicode != ( TELUGU_DELTA ) || sourceChar != VOCALLIC_RR ) {
 targetByteUnit = missingCharMarker ;
 }
 }
 if ( deltaChanged ) {
 uint32_t temp = 0 ;
 temp = ( uint16_t ) ( ATR << 8 ) ;
 temp += ( uint16_t ) ( ( uint8_t ) lookupInitialData [ range ] . isciiLang ) ;
 deltaChanged = FALSE ;
 WRITE_TO_TARGET_FROM_U ( args , offsets , source , target , targetLimit , temp , err ) ;
 if ( U_FAILURE ( * err ) ) {
 break ;
 }
 }
 if ( converterData -> currentDeltaFromUnicode == PNJ_DELTA && ( sourceChar + PNJ_DELTA ) == PNJ_ADHAK ) {
 continue ;
 }
 }
 converterData -> contextCharFromUnicode = 0x00 ;
 break ;
 }
 if ( converterData -> currentDeltaFromUnicode == PNJ_DELTA && tempContextFromUnicode == PNJ_ADHAK && isPNJConsonant ( ( sourceChar + PNJ_DELTA ) ) ) {
 converterData -> contextCharFromUnicode = 0x0000 ;
 targetByteUnit = targetByteUnit << 16 | ISCII_HALANT << 8 | targetByteUnit ;
 WRITE_TO_TARGET_FROM_U ( args , offsets , source , target , targetLimit , targetByteUnit , err ) ;
 if ( U_FAILURE ( * err ) ) {
 break ;
 }
 }
 else if ( targetByteUnit != missingCharMarker ) {
 if ( targetByteUnit == ISCII_HALANT ) {
 converterData -> contextCharFromUnicode = ( UChar ) targetByteUnit ;
 }
 WRITE_TO_TARGET_FROM_U ( args , offsets , source , target , targetLimit , targetByteUnit , err ) ;
 if ( U_FAILURE ( * err ) ) {
 break ;
 }
 }
 else {
 if ( U16_IS_SURROGATE ( sourceChar ) ) {
 if ( U16_IS_SURROGATE_LEAD ( sourceChar ) ) {
 getTrail : if ( source < sourceLimit ) {
 UChar trail = ( * source ) ;
 if ( U16_IS_TRAIL ( trail ) ) {
 source ++ ;
 sourceChar = U16_GET_SUPPLEMENTARY ( sourceChar , trail ) ;
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
 args -> converter -> fromUChar32 = sourceChar ;
 break ;
 }
 }
 args -> source = source ;
 args -> target = ( char * ) target ;
 }