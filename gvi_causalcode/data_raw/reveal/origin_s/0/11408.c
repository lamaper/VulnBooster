static void _fromUnicodeWithCallback ( UConverterFromUnicodeArgs * pArgs , UErrorCode * err ) {
 UConverterFromUnicode fromUnicode ;
 UConverter * cnv ;
 const UChar * s ;
 char * t ;
 int32_t * offsets ;
 int32_t sourceIndex ;
 int32_t errorInputLength ;
 UBool converterSawEndOfInput , calledCallback ;
 UChar replay [ UCNV_EXT_MAX_UCHARS ] ;
 const UChar * realSource , * realSourceLimit ;
 int32_t realSourceIndex ;
 UBool realFlush ;
 cnv = pArgs -> converter ;
 s = pArgs -> source ;
 t = pArgs -> target ;
 offsets = pArgs -> offsets ;
 sourceIndex = 0 ;
 if ( offsets == NULL ) {
 fromUnicode = cnv -> sharedData -> impl -> fromUnicode ;
 }
 else {
 fromUnicode = cnv -> sharedData -> impl -> fromUnicodeWithOffsets ;
 if ( fromUnicode == NULL ) {
 fromUnicode = cnv -> sharedData -> impl -> fromUnicode ;
 sourceIndex = - 1 ;
 }
 }
 if ( cnv -> preFromULength >= 0 ) {
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
 uprv_memcpy ( replay , cnv -> preFromU , - cnv -> preFromULength * U_SIZEOF_UCHAR ) ;
 pArgs -> source = replay ;
 pArgs -> sourceLimit = replay - cnv -> preFromULength ;
 pArgs -> flush = FALSE ;
 sourceIndex = - 1 ;
 cnv -> preFromULength = 0 ;
 }
 for ( ;
 ;
 ) {
 if ( U_SUCCESS ( * err ) ) {
 fromUnicode ( pArgs , err ) ;
 converterSawEndOfInput = ( UBool ) ( U_SUCCESS ( * err ) && pArgs -> flush && pArgs -> source == pArgs -> sourceLimit && cnv -> fromUChar32 == 0 ) ;
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
 if ( cnv -> preFromULength < 0 ) {
 if ( realSource == NULL ) {
 realSource = pArgs -> source ;
 realSourceLimit = pArgs -> sourceLimit ;
 realFlush = pArgs -> flush ;
 realSourceIndex = sourceIndex ;
 uprv_memcpy ( replay , cnv -> preFromU , - cnv -> preFromULength * U_SIZEOF_UCHAR ) ;
 pArgs -> source = replay ;
 pArgs -> sourceLimit = replay - cnv -> preFromULength ;
 pArgs -> flush = FALSE ;
 if ( ( sourceIndex += cnv -> preFromULength ) < 0 ) {
 sourceIndex = - 1 ;
 }
 cnv -> preFromULength = 0 ;
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
 else if ( pArgs -> flush && cnv -> fromUChar32 != 0 ) {
 * err = U_TRUNCATED_CHAR_FOUND ;
 calledCallback = FALSE ;
 }
 else {
 if ( pArgs -> flush ) {
 if ( ! converterSawEndOfInput ) {
 break ;
 }
 _reset ( cnv , UCNV_RESET_FROM_UNICODE , FALSE ) ;
 }
 return ;
 }
 }
 {
 UErrorCode e ;
 if ( calledCallback || ( e = * err ) == U_BUFFER_OVERFLOW_ERROR || ( e != U_INVALID_CHAR_FOUND && e != U_ILLEGAL_CHAR_FOUND && e != U_TRUNCATED_CHAR_FOUND ) ) {
 if ( realSource != NULL ) {
 int32_t length ;
 U_ASSERT ( cnv -> preFromULength == 0 ) ;
 length = ( int32_t ) ( pArgs -> sourceLimit - pArgs -> source ) ;
 if ( length > 0 ) {
 u_memcpy ( cnv -> preFromU , pArgs -> source , length ) ;
 cnv -> preFromULength = ( int8_t ) - length ;
 }
 pArgs -> source = realSource ;
 pArgs -> sourceLimit = realSourceLimit ;
 pArgs -> flush = realFlush ;
 }
 return ;
 }
 }
 {
 UChar32 codePoint ;
 codePoint = cnv -> fromUChar32 ;
 errorInputLength = 0 ;
 U16_APPEND_UNSAFE ( cnv -> invalidUCharBuffer , errorInputLength , codePoint ) ;
 cnv -> invalidUCharLength = ( int8_t ) errorInputLength ;
 cnv -> fromUChar32 = 0 ;
 cnv -> fromUCharErrorBehaviour ( cnv -> fromUContext , pArgs , cnv -> invalidUCharBuffer , errorInputLength , codePoint , * err == U_INVALID_CHAR_FOUND ? UCNV_UNASSIGNED : UCNV_ILLEGAL , err ) ;
 }
 calledCallback = TRUE ;
 }
 }
 }