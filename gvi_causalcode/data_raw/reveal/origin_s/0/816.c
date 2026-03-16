static void U_CALLCONV _SCSUReset ( UConverter * cnv , UConverterResetChoice choice ) {
 SCSUData * scsu = ( SCSUData * ) cnv -> extraInfo ;
 if ( choice <= UCNV_RESET_TO_UNICODE ) {
 uprv_memcpy ( scsu -> toUDynamicOffsets , initialDynamicOffsets , 32 ) ;
 scsu -> toUIsSingleByteMode = TRUE ;
 scsu -> toUState = readCommand ;
 scsu -> toUQuoteWindow = scsu -> toUDynamicWindow = 0 ;
 scsu -> toUByteOne = 0 ;
 cnv -> toULength = 0 ;
 }
 if ( choice != UCNV_RESET_TO_UNICODE ) {
 uprv_memcpy ( scsu -> fromUDynamicOffsets , initialDynamicOffsets , 32 ) ;
 scsu -> fromUIsSingleByteMode = TRUE ;
 scsu -> fromUDynamicWindow = 0 ;
 scsu -> nextWindowUseIndex = 0 ;
 switch ( scsu -> locale ) {
 case l_ja : uprv_memcpy ( scsu -> windowUse , initialWindowUse_ja , 8 ) ;
 break ;
 default : uprv_memcpy ( scsu -> windowUse , initialWindowUse , 8 ) ;
 break ;
 }
 cnv -> fromUChar32 = 0 ;
 }
 }