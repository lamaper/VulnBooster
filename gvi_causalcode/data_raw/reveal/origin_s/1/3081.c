static void _ISCIIReset ( UConverter * cnv , UConverterResetChoice choice ) {
 UConverterDataISCII * data = ( UConverterDataISCII * ) ( cnv -> extraInfo ) ;
 if ( choice <= UCNV_RESET_TO_UNICODE ) {
 cnv -> toUnicodeStatus = missingCharMarker ;
 cnv -> mode = 0 ;
 data -> currentDeltaToUnicode = data -> defDeltaToUnicode ;
 data -> currentMaskToUnicode = data -> defMaskToUnicode ;
 data -> contextCharToUnicode = NO_CHAR_MARKER ;
 data -> prevToUnicodeStatus = 0x0000 ;
 }
 if ( choice != UCNV_RESET_TO_UNICODE ) {
 cnv -> fromUChar32 = 0x0000 ;
 data -> contextCharFromUnicode = 0x00 ;
 data -> currentMaskFromUnicode = data -> defMaskToUnicode ;
 data -> currentDeltaFromUnicode = data -> defDeltaToUnicode ;
 data -> isFirstBuffer = TRUE ;
 data -> resetToDefaultToUnicode = FALSE ;
 }
 }