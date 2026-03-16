static void _toUnicodeWithCallback ( UConverterToUnicodeArgs * pArgs , UErrorCode * err ) {
 UConverterToUnicode toUnicode ;
 UConverter * cnv ;
 const char * s ;
 UChar * t ;
 int32_t * offsets ;
 int32_t sourceIndex ;
 int32_t errorInputLength ;
 UBool converterSawEndOfInput , calledCallback ;
 char replay [ UCNV_EXT_MAX_BYTES ] ;
 const char * realSource , * realSourceLimit ;
 int32_t realSourceIndex ;
 UBool realFlush ;
 cnv = pArgs -> converter ;
 s = pArgs -> source ;
 t = pArgs -> target ;
 offsets = pArgs -> offsets ;
 sourceIndex = 0 ;
 if ( offsets == NULL ) {
 toUnicode = cnv -> sharedData -> impl -> toUnicode ;
 }
 else {
 toUnicode = cnv -> sharedData -> impl -> toUnicodeWithOffsets ;
 if ( toUnicode == NULL ) {
 toUnicode = cnv -> sharedData -> impl -> toUnicode ;
 sourceIndex = - 1 ;
 }
 }
 if ( cnv -> preToULength >= 0 ) {
 realSource = NULL ;
 realSourceLimit = NULL ;
 realFlush = FALSE ;
 realSourceIndex = 0 ;
 }
 else {
 realSource = pArgs -> source ;
 realSourceLimit = pArgs -> sourceLimit ;
 realFlush = pArgs -> flush ;
 realSourceIndex = sourceIndex ;
 uprv_memcpy ( replay , cnv -> preToU , - cnv -> preToULength ) ;
 pArgs -> source = replay ;
 pArgs -> sourceLimit = replay - cnv -> preToULength ;
 pArgs -> flush = FALSE ;
 sourceIndex = - 1 ;
 cnv -> preToULength = 0 ;
 }
 for ( ;
 ;
 ) {
 if ( U_SUCCESS ( * err ) ) {
 toUnicode ( pArgs , err ) ;
 converterSawEndOfInput = ( UBool ) ( U_SUCCESS ( * err ) && pArgs -> flush && pArgs -> source == pArgs -> sourceLimit && cnv -> toULength == 0 ) ;
 }
 else {
 converterSawEndOfInput = FALSE ;
 }
 calledCallback = FALSE ;
 errorInputLength = 0 ;
 for ( ;
 ;
 ) {
 if ( offsets != NULL ) {
 int32_t length = ( int32_t ) ( pArgs -> target - t ) ;
 if ( length > 0 ) {
 _updateOffsets ( offsets , length , sourceIndex , errorInputLength ) ;
 pArgs -> offsets = offsets += length ;
 }
 if ( sourceIndex >= 0 ) {
 sourceIndex += ( int32_t ) ( pArgs -> source - s ) ;
 }
 }
 if ( cnv -> preToULength < 0 ) {
 if ( realSource == NULL ) {
 realSource = pArgs -> source ;
 realSourceLimit = pArgs -> sourceLimit ;
 realFlush = pArgs -> flush ;
 realSourceIndex = sourceIndex ;
 uprv_memcpy ( replay , cnv -> preToU , - cnv -> preToULength ) ;
 pArgs -> source = replay ;
 pArgs -> sourceLimit = replay - cnv -> preToULength ;
 pArgs -> flush = FALSE ;
 if ( ( sourceIndex += cnv -> preToULength ) < 0 ) {
 sourceIndex = - 1 ;
 }
 cnv -> preToULength = 0 ;
 }
 else {
 U_ASSERT ( realSource == NULL ) ;
 * err = U_INTERNAL_PROGRAM_ERROR ;
 }
 }
 s = pArgs -> source ;
 t = pArgs -> target ;
 if ( U_SUCCESS ( * err ) ) {
 if ( s < pArgs -> sourceLimit ) {
 break ;
 }
 else if ( realSource != NULL ) {
 pArgs -> source = realSource ;
 pArgs -> sourceLimit = realSourceLimit ;
 pArgs -> flush = realFlush ;
 sourceIndex = realSourceIndex ;
 realSource = NULL ;
 break ;
 }
 else if ( pArgs -> flush && cnv -> toULength > 0 ) {
 * err = U_TRUNCATED_CHAR_FOUND ;
 calledCallback = FALSE ;
 }
 else {
 if ( pArgs -> flush ) {
 if ( ! converterSawEndOfInput ) {
 break ;
 }
 _reset ( cnv , UCNV_RESET_TO_UNICODE , FALSE ) ;
 }
 return ;
 }
 }
 {
 UErrorCode e ;
 if ( calledCallback || ( e = * err ) == U_BUFFER_OVERFLOW_ERROR || ( e != U_INVALID_CHAR_FOUND && e != U_ILLEGAL_CHAR_FOUND && e != U_TRUNCATED_CHAR_FOUND && e != U_ILLEGAL_ESCAPE_SEQUENCE && e != U_UNSUPPORTED_ESCAPE_SEQUENCE ) ) {
 if ( realSource != NULL ) {
 int32_t length ;
 U_ASSERT ( cnv -> preToULength == 0 ) ;
 length = ( int32_t ) ( pArgs -> sourceLimit - pArgs -> source ) ;
 if ( length > 0 ) {
 uprv_memcpy ( cnv -> preToU , pArgs -> source , length ) ;
 cnv -> preToULength = ( int8_t ) - length ;
 }
 pArgs -> source = realSource ;
 pArgs -> sourceLimit = realSourceLimit ;
 pArgs -> flush = realFlush ;
 }
 return ;
 }
 }
 errorInputLength = cnv -> invalidCharLength = cnv -> toULength ;
 if ( errorInputLength > 0 ) {
 uprv_memcpy ( cnv -> invalidCharBuffer , cnv -> toUBytes , errorInputLength ) ;
 }
 cnv -> toULength = 0 ;
 if ( cnv -> toUCallbackReason == UCNV_ILLEGAL && * err == U_INVALID_CHAR_FOUND ) {
 cnv -> toUCallbackReason = UCNV_UNASSIGNED ;
 }
 cnv -> fromCharErrorBehaviour ( cnv -> toUContext , pArgs , cnv -> invalidCharBuffer , errorInputLength , cnv -> toUCallbackReason , err ) ;
 cnv -> toUCallbackReason = UCNV_ILLEGAL ;
 calledCallback = TRUE ;
 }
 }
 }