static void _HZReset ( UConverter * cnv , UConverterResetChoice choice ) {
 if ( choice <= UCNV_RESET_TO_UNICODE ) {
 cnv -> toUnicodeStatus = 0 ;
 cnv -> mode = 0 ;
 if ( cnv -> extraInfo != NULL ) {
 ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> isStateDBCS = FALSE ;
 ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> isEmptySegment = FALSE ;
 }
 }
 if ( choice != UCNV_RESET_TO_UNICODE ) {
 cnv -> fromUnicodeStatus = 0 ;
 cnv -> fromUChar32 = 0x0000 ;
 if ( cnv -> extraInfo != NULL ) {
 ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> isEscapeAppended = FALSE ;
 ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> targetIndex = 0 ;
 ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> sourceIndex = 0 ;
 ( ( UConverterDataHZ * ) cnv -> extraInfo ) -> isTargetUCharDBCS = FALSE ;
 }
 }
 }