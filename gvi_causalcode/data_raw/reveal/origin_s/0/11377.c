static void U_CALLCONV UConverter_toUnicode_ISCII_OFFSETS_LOGIC ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 const char * source = ( char * ) args -> source ;
 UChar * target = args -> target ;
 const char * sourceLimit = args -> sourceLimit ;
 const UChar * targetLimit = args -> targetLimit ;
 uint32_t targetUniChar = 0x0000 ;
 uint8_t sourceChar = 0x0000 ;
 UConverterDataISCII * data ;
 UChar32 * toUnicodeStatus = NULL ;
 UChar32 tempTargetUniChar = 0x0000 ;
 UChar * contextCharToUnicode = NULL ;
 UBool found ;
 int i ;
 int offset = 0 ;
 if ( ( args -> converter == NULL ) || ( target < args -> target ) || ( source < args -> source ) ) {
 * err = U_ILLEGAL_ARGUMENT_ERROR ;
 return ;
 }
 data = ( UConverterDataISCII * ) ( args -> converter -> extraInfo ) ;
 contextCharToUnicode = & data -> contextCharToUnicode ;
 toUnicodeStatus = ( UChar32 * ) & args -> converter -> toUnicodeStatus ;
 while ( U_SUCCESS ( * err ) && source < sourceLimit ) {
 targetUniChar = missingCharMarker ;
 if ( target < targetLimit ) {
 sourceChar = ( unsigned char ) * ( source ) ++ ;
 if ( * contextCharToUnicode == ATR ) {
 if ( ( uint8_t ) ( PNJ - sourceChar ) <= PNJ - DEV ) {
 data -> currentDeltaToUnicode = ( uint16_t ) ( lookupTable [ sourceChar & 0x0F ] [ 0 ] * DELTA ) ;
 data -> currentMaskToUnicode = ( MaskEnum ) lookupTable [ sourceChar & 0x0F ] [ 1 ] ;
 }
 else if ( sourceChar == DEF ) {
 data -> currentDeltaToUnicode = data -> defDeltaToUnicode ;
 data -> currentMaskToUnicode = data -> defMaskToUnicode ;
 }
 else {
 if ( ( sourceChar >= 0x21 && sourceChar <= 0x3F ) ) {
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 * contextCharToUnicode = NO_CHAR_MARKER ;
 goto CALLBACK ;
 }
 }
 * contextCharToUnicode = NO_CHAR_MARKER ;
 continue ;
 }
 else if ( * contextCharToUnicode == EXT ) {
 if ( ( uint8_t ) ( EXT_RANGE_END - sourceChar ) <= ( EXT_RANGE_END - EXT_RANGE_BEGIN ) ) {
 if ( sourceChar == 0xBF || sourceChar == 0xB8 ) {
 targetUniChar = ( sourceChar == 0xBF ) ? DEV_ABBR_SIGN : DEV_ANUDATTA ;
 if ( validityTable [ ( uint8_t ) targetUniChar ] & data -> currentMaskToUnicode ) {
 * contextCharToUnicode = NO_CHAR_MARKER ;
 if ( data -> prevToUnicodeStatus ) {
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 1 ) , data -> prevToUnicodeStatus , 0 , err ) ;
 data -> prevToUnicodeStatus = 0x0000 ;
 }
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 2 ) , targetUniChar , data -> currentDeltaToUnicode , err ) ;
 continue ;
 }
 }
 targetUniChar = missingCharMarker ;
 * err = U_INVALID_CHAR_FOUND ;
 }
 else {
 * contextCharToUnicode = NO_CHAR_MARKER ;
 * err = U_ILLEGAL_CHAR_FOUND ;
 }
 goto CALLBACK ;
 }
 else if ( * contextCharToUnicode == ISCII_INV ) {
 if ( sourceChar == ISCII_HALANT ) {
 targetUniChar = 0x0020 ;
 }
 else {
 targetUniChar = ZWJ ;
 }
 if ( data -> prevToUnicodeStatus ) {
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 1 ) , data -> prevToUnicodeStatus , 0 , err ) ;
 data -> prevToUnicodeStatus = 0x0000 ;
 }
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 2 ) , targetUniChar , data -> currentDeltaToUnicode , err ) ;
 * contextCharToUnicode = NO_CHAR_MARKER ;
 }
 switch ( sourceChar ) {
 case ISCII_INV : case EXT : case ATR : * contextCharToUnicode = ( UChar ) sourceChar ;
 if ( * toUnicodeStatus != missingCharMarker ) {
 if ( data -> prevToUnicodeStatus ) {
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 1 ) , data -> prevToUnicodeStatus , 0 , err ) ;
 data -> prevToUnicodeStatus = 0x0000 ;
 }
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 2 ) , * toUnicodeStatus , data -> currentDeltaToUnicode , err ) ;
 * toUnicodeStatus = missingCharMarker ;
 }
 continue ;
 case ISCII_DANDA : if ( * contextCharToUnicode == ISCII_DANDA ) {
 targetUniChar = DOUBLE_DANDA ;
 * contextCharToUnicode = NO_CHAR_MARKER ;
 * toUnicodeStatus = missingCharMarker ;
 }
 else {
 GET_MAPPING ( sourceChar , targetUniChar , data ) ;
 * contextCharToUnicode = sourceChar ;
 }
 break ;
 case ISCII_HALANT : if ( * contextCharToUnicode == ISCII_HALANT ) {
 targetUniChar = ZWNJ ;
 * contextCharToUnicode = NO_CHAR_MARKER ;
 }
 else {
 GET_MAPPING ( sourceChar , targetUniChar , data ) ;
 * contextCharToUnicode = sourceChar ;
 }
 break ;
 case 0x0A : case 0x0D : data -> resetToDefaultToUnicode = TRUE ;
 GET_MAPPING ( sourceChar , targetUniChar , data ) ;
 * contextCharToUnicode = sourceChar ;
 break ;
 case ISCII_VOWEL_SIGN_E : i = 1 ;
 found = FALSE ;
 for ( ;
 i < vowelSignESpecialCases [ 0 ] [ 0 ] ;
 i ++ ) {
 U_ASSERT ( i < UPRV_LENGTHOF ( vowelSignESpecialCases ) ) ;
 if ( vowelSignESpecialCases [ i ] [ 0 ] == ( uint8_t ) * contextCharToUnicode ) {
 targetUniChar = vowelSignESpecialCases [ i ] [ 1 ] ;
 found = TRUE ;
 break ;
 }
 }
 if ( found ) {
 if ( validityTable [ ( uint8_t ) targetUniChar ] & data -> currentMaskToUnicode ) {
 * contextCharToUnicode = NO_CHAR_MARKER ;
 * toUnicodeStatus = missingCharMarker ;
 break ;
 }
 }
 GET_MAPPING ( sourceChar , targetUniChar , data ) ;
 * contextCharToUnicode = sourceChar ;
 break ;
 case ISCII_NUKTA : if ( * contextCharToUnicode == ISCII_HALANT ) {
 targetUniChar = ZWJ ;
 * contextCharToUnicode = NO_CHAR_MARKER ;
 break ;
 }
 else if ( data -> currentDeltaToUnicode == PNJ_DELTA && data -> contextCharToUnicode == 0xc0 ) {
 if ( data -> prevToUnicodeStatus ) {
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 1 ) , data -> prevToUnicodeStatus , 0 , err ) ;
 data -> prevToUnicodeStatus = 0x0000 ;
 }
 targetUniChar = PNJ_RRA ;
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source ) - 2 , targetUniChar , 0 , err ) ;
 if ( U_SUCCESS ( * err ) ) {
 targetUniChar = PNJ_SIGN_VIRAMA ;
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source ) - 2 , targetUniChar , 0 , err ) ;
 if ( U_SUCCESS ( * err ) ) {
 targetUniChar = PNJ_HA ;
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source ) - 2 , targetUniChar , 0 , err ) ;
 }
 else {
 args -> converter -> UCharErrorBuffer [ args -> converter -> UCharErrorBufferLength ++ ] = PNJ_HA ;
 }
 }
 else {
 args -> converter -> UCharErrorBuffer [ args -> converter -> UCharErrorBufferLength ++ ] = PNJ_SIGN_VIRAMA ;
 args -> converter -> UCharErrorBuffer [ args -> converter -> UCharErrorBufferLength ++ ] = PNJ_HA ;
 }
 * toUnicodeStatus = missingCharMarker ;
 data -> contextCharToUnicode = NO_CHAR_MARKER ;
 continue ;
 }
 else {
 i = 1 ;
 found = FALSE ;
 for ( ;
 i < nuktaSpecialCases [ 0 ] [ 0 ] ;
 i ++ ) {
 if ( nuktaSpecialCases [ i ] [ 0 ] == ( uint8_t ) * contextCharToUnicode ) {
 targetUniChar = nuktaSpecialCases [ i ] [ 1 ] ;
 found = TRUE ;
 break ;
 }
 }
 if ( found ) {
 if ( validityTable [ ( uint8_t ) targetUniChar ] & data -> currentMaskToUnicode ) {
 * contextCharToUnicode = NO_CHAR_MARKER ;
 * toUnicodeStatus = missingCharMarker ;
 if ( data -> currentDeltaToUnicode == PNJ_DELTA ) {
 if ( data -> prevToUnicodeStatus ) {
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 1 ) , data -> prevToUnicodeStatus , 0 , err ) ;
 data -> prevToUnicodeStatus = 0x0000 ;
 }
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 2 ) , targetUniChar , data -> currentDeltaToUnicode , err ) ;
 continue ;
 }
 break ;
 }
 }
 U_FALLTHROUGH ;
 }
 default : GET_MAPPING ( sourceChar , targetUniChar , data ) ;
 * contextCharToUnicode = sourceChar ;
 break ;
 }
 if ( * toUnicodeStatus != missingCharMarker ) {
 if ( data -> currentDeltaToUnicode == PNJ_DELTA && data -> prevToUnicodeStatus != 0 && isPNJConsonant ( data -> prevToUnicodeStatus ) && ( * toUnicodeStatus + PNJ_DELTA ) == PNJ_SIGN_VIRAMA && ( ( UChar32 ) ( targetUniChar + PNJ_DELTA ) == data -> prevToUnicodeStatus ) ) {
 offset = ( int ) ( source - args -> source - 3 ) ;
 tempTargetUniChar = PNJ_ADHAK ;
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , offset , tempTargetUniChar , 0 , err ) ;
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , offset , data -> prevToUnicodeStatus , 0 , err ) ;
 data -> prevToUnicodeStatus = 0x0000 ;
 * toUnicodeStatus = missingCharMarker ;
 continue ;
 }
 else {
 if ( data -> prevToUnicodeStatus ) {
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 1 ) , data -> prevToUnicodeStatus , 0 , err ) ;
 data -> prevToUnicodeStatus = 0x0000 ;
 }
 if ( data -> currentDeltaToUnicode == PNJ_DELTA && ( targetUniChar + PNJ_DELTA ) == PNJ_BINDI && isPNJBindiTippi ( ( * toUnicodeStatus + PNJ_DELTA ) ) ) {
 targetUniChar = PNJ_TIPPI - PNJ_DELTA ;
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 2 ) , * toUnicodeStatus , PNJ_DELTA , err ) ;
 }
 else if ( data -> currentDeltaToUnicode == PNJ_DELTA && ( targetUniChar + PNJ_DELTA ) == PNJ_SIGN_VIRAMA && isPNJConsonant ( ( * toUnicodeStatus + PNJ_DELTA ) ) ) {
 data -> prevToUnicodeStatus = * toUnicodeStatus + PNJ_DELTA ;
 }
 else {
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 2 ) , * toUnicodeStatus , data -> currentDeltaToUnicode , err ) ;
 }
 }
 * toUnicodeStatus = missingCharMarker ;
 }
 if ( targetUniChar != missingCharMarker ) {
 * toUnicodeStatus = ( UChar ) targetUniChar ;
 if ( data -> resetToDefaultToUnicode == TRUE ) {
 data -> currentDeltaToUnicode = data -> defDeltaToUnicode ;
 data -> currentMaskToUnicode = data -> defMaskToUnicode ;
 data -> resetToDefaultToUnicode = FALSE ;
 }
 }
 else {
 * err = U_INVALID_CHAR_FOUND ;
 CALLBACK : args -> converter -> toUBytes [ 0 ] = ( uint8_t ) sourceChar ;
 args -> converter -> toULength = 1 ;
 break ;
 }
 }
 else {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 if ( U_SUCCESS ( * err ) && args -> flush && source == sourceLimit ) {
 UConverter * cnv = args -> converter ;
 if ( * contextCharToUnicode == ATR || * contextCharToUnicode == EXT || * contextCharToUnicode == ISCII_INV ) {
 cnv -> toUBytes [ 0 ] = ( uint8_t ) * contextCharToUnicode ;
 cnv -> toULength = 1 ;
 * contextCharToUnicode = NO_CHAR_MARKER ;
 }
 else {
 cnv -> toULength = 0 ;
 }
 if ( * toUnicodeStatus != missingCharMarker ) {
 WRITE_TO_TARGET_TO_U ( args , source , target , args -> offsets , ( source - args -> source - 1 ) , * toUnicodeStatus , data -> currentDeltaToUnicode , err ) ;
 * toUnicodeStatus = missingCharMarker ;
 }
 }
 args -> target = target ;
 args -> source = source ;
 }