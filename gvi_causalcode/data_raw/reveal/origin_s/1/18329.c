static void UConverter_toUnicode_CompoundText_OFFSETS ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 const char * mySource = ( char * ) args -> source ;
 UChar * myTarget = args -> target ;
 const char * mySourceLimit = args -> sourceLimit ;
 const char * tmpSourceLimit = mySourceLimit ;
 uint32_t mySourceChar = 0x0000 ;
 COMPOUND_TEXT_CONVERTERS currentState , tmpState ;
 int32_t sourceOffset = 0 ;
 UConverterDataCompoundText * myConverterData = ( UConverterDataCompoundText * ) args -> converter -> extraInfo ;
 UConverterSharedData * savedSharedData = NULL ;
 UConverterToUnicodeArgs subArgs ;
 int32_t minArgsSize ;
 if ( args -> size < sizeof ( UConverterToUnicodeArgs ) ) {
 minArgsSize = args -> size ;
 }
 else {
 minArgsSize = ( int32_t ) sizeof ( UConverterToUnicodeArgs ) ;
 }
 uprv_memcpy ( & subArgs , args , minArgsSize ) ;
 subArgs . size = ( uint16_t ) minArgsSize ;
 currentState = tmpState = myConverterData -> state ;
 while ( mySource < mySourceLimit ) {
 if ( myTarget < args -> targetLimit ) {
 if ( args -> converter -> toULength > 0 ) {
 mySourceChar = args -> converter -> toUBytes [ 0 ] ;
 }
 else {
 mySourceChar = ( uint8_t ) * mySource ;
 }
 if ( mySourceChar == ESC_START ) {
 tmpState = findStateFromEscSeq ( mySource , mySourceLimit , args -> converter -> toUBytes , args -> converter -> toULength , err ) ;
 if ( * err == U_TRUNCATED_CHAR_FOUND ) {
 for ( ;
 mySource < mySourceLimit ;
 ) {
 args -> converter -> toUBytes [ args -> converter -> toULength ++ ] = * mySource ++ ;
 }
 * err = U_ZERO_ERROR ;
 break ;
 }
 else if ( tmpState == INVALID ) {
 if ( args -> converter -> toULength == 0 ) {
 mySource ++ ;
 }
 * err = U_ILLEGAL_CHAR_FOUND ;
 break ;
 }
 if ( tmpState != currentState ) {
 currentState = tmpState ;
 }
 sourceOffset = uprv_strlen ( ( char * ) escSeqCompoundText [ currentState ] ) - args -> converter -> toULength ;
 mySource += sourceOffset ;
 args -> converter -> toULength = 0 ;
 }
 if ( currentState == COMPOUND_TEXT_SINGLE_0 ) {
 while ( mySource < mySourceLimit ) {
 if ( * mySource == ESC_START ) {
 break ;
 }
 if ( myTarget < args -> targetLimit ) {
 * myTarget ++ = 0x00ff & ( * mySource ++ ) ;
 }
 else {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 }
 else if ( mySource < mySourceLimit ) {
 sourceOffset = findNextEsc ( mySource , mySourceLimit ) ;
 tmpSourceLimit = mySource + sourceOffset ;
 subArgs . source = mySource ;
 subArgs . sourceLimit = tmpSourceLimit ;
 subArgs . target = myTarget ;
 savedSharedData = subArgs . converter -> sharedData ;
 subArgs . converter -> sharedData = myConverterData -> myConverterArray [ currentState ] ;
 ucnv_MBCSToUnicodeWithOffsets ( & subArgs , err ) ;
 subArgs . converter -> sharedData = savedSharedData ;
 mySource = subArgs . source ;
 myTarget = subArgs . target ;
 if ( U_FAILURE ( * err ) ) {
 if ( * err == U_BUFFER_OVERFLOW_ERROR ) {
 if ( subArgs . converter -> UCharErrorBufferLength > 0 ) {
 uprv_memcpy ( args -> converter -> UCharErrorBuffer , subArgs . converter -> UCharErrorBuffer , subArgs . converter -> UCharErrorBufferLength ) ;
 }
 args -> converter -> UCharErrorBufferLength = subArgs . converter -> UCharErrorBufferLength ;
 subArgs . converter -> UCharErrorBufferLength = 0 ;
 }
 break ;
 }
 }
 }
 else {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 break ;
 }
 }
 myConverterData -> state = currentState ;
 args -> target = myTarget ;
 args -> source = mySource ;
 }