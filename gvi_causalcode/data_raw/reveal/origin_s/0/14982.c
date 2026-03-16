static void U_CALLCONV UConverter_fromUnicode_CompoundText_OFFSETS ( UConverterFromUnicodeArgs * args , UErrorCode * err ) {
 UConverter * cnv = args -> converter ;
 uint8_t * target = ( uint8_t * ) args -> target ;
 const uint8_t * targetLimit = ( const uint8_t * ) args -> targetLimit ;
 const UChar * source = args -> source ;
 const UChar * sourceLimit = args -> sourceLimit ;
 UChar32 sourceChar ;
 UBool useFallback = cnv -> useFallback ;
 uint8_t tmpTargetBuffer [ 7 ] ;
 int32_t tmpTargetBufferLength = 0 ;
 COMPOUND_TEXT_CONVERTERS currentState , tmpState ;
 uint32_t pValue ;
 int32_t pValueLength = 0 ;
 int32_t i , n , j ;
 UConverterDataCompoundText * myConverterData = ( UConverterDataCompoundText * ) cnv -> extraInfo ;
 currentState = myConverterData -> state ;
 if ( ( sourceChar = cnv -> fromUChar32 ) != 0 && target < targetLimit ) {
 goto getTrail ;
 }
 while ( source < sourceLimit ) {
 if ( target < targetLimit ) {
 sourceChar = * ( source ++ ) ;
 if ( U16_IS_SURROGATE ( sourceChar ) ) {
 if ( U16_IS_SURROGATE_LEAD ( sourceChar ) ) {
 getTrail : if ( source < sourceLimit ) {
 UChar trail = ( UChar ) * source ;
 if ( U16_IS_TRAIL ( trail ) ) {
 source ++ ;
 sourceChar = U16_GET_SUPPLEMENTARY ( sourceChar , trail ) ;
 cnv -> fromUChar32 = 0x00 ;
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 cnv -> fromUChar32 = sourceChar ;
 break ;
 }
 }
 else {
 cnv -> fromUChar32 = sourceChar ;
 break ;
 }
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 cnv -> fromUChar32 = sourceChar ;
 break ;
 }
 }
 tmpTargetBufferLength = 0 ;
 tmpState = getState ( sourceChar ) ;
 if ( tmpState != DO_SEARCH && currentState != tmpState ) {
 currentState = tmpState ;
 for ( i = 0 ;
 escSeqCompoundText [ currentState ] [ i ] != 0 ;
 i ++ ) {
 tmpTargetBuffer [ tmpTargetBufferLength ++ ] = escSeqCompoundText [ currentState ] [ i ] ;
 }
 }
 if ( tmpState == DO_SEARCH ) {
 for ( i = 1 ;
 i < SEARCH_LENGTH ;
 i ++ ) {
 pValueLength = ucnv_MBCSFromUChar32 ( myConverterData -> myConverterArray [ i ] , sourceChar , & pValue , useFallback ) ;
 if ( pValueLength > 0 ) {
 tmpState = ( COMPOUND_TEXT_CONVERTERS ) i ;
 if ( currentState != tmpState ) {
 currentState = tmpState ;
 for ( j = 0 ;
 escSeqCompoundText [ currentState ] [ j ] != 0 ;
 j ++ ) {
 tmpTargetBuffer [ tmpTargetBufferLength ++ ] = escSeqCompoundText [ currentState ] [ j ] ;
 }
 }
 for ( n = ( pValueLength - 1 ) ;
 n >= 0 ;
 n -- ) {
 tmpTargetBuffer [ tmpTargetBufferLength ++ ] = ( uint8_t ) ( pValue >> ( n * 8 ) ) ;
 }
 break ;
 }
 }
 }
 else if ( tmpState == COMPOUND_TEXT_SINGLE_0 ) {
 tmpTargetBuffer [ tmpTargetBufferLength ++ ] = ( uint8_t ) sourceChar ;
 }
 else {
 pValueLength = ucnv_MBCSFromUChar32 ( myConverterData -> myConverterArray [ currentState ] , sourceChar , & pValue , useFallback ) ;
 if ( pValueLength > 0 ) {
 for ( n = ( pValueLength - 1 ) ;
 n >= 0 ;
 n -- ) {
 tmpTargetBuffer [ tmpTargetBufferLength ++ ] = ( uint8_t ) ( pValue >> ( n * 8 ) ) ;
 }
 }
 }
 for ( i = 0 ;
 i < tmpTargetBufferLength ;
 i ++ ) {
 if ( target < targetLimit ) {
 * target ++ = tmpTargetBuffer [ i ] ;
 }
 else {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 if ( * err == U_BUFFER_OVERFLOW_ERROR ) {
 for ( ;
 i < tmpTargetBufferLength ;
 i ++ ) {
 args -> converter -> charErrorBuffer [ args -> converter -> charErrorBufferLength ++ ] = tmpTargetBuffer [ i ] ;
 }
 }
 }
 else {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 myConverterData -> state = currentState ;
 args -> source = source ;
 args -> target = ( char * ) target ;
 }