static void U_CALLCONV _LMBCSToUnicodeWithOffsets ( UConverterToUnicodeArgs * args , UErrorCode * err ) {
 char LMBCS [ ULMBCS_CHARSIZE_MAX ] ;
 UChar uniChar ;
 const char * saveSource ;
 const char * pStartLMBCS = args -> source ;
 const char * errSource = NULL ;
 int8_t savebytes = 0 ;
 while ( U_SUCCESS ( * err ) && args -> sourceLimit > args -> source && args -> targetLimit > args -> target ) {
 saveSource = args -> source ;
 if ( args -> converter -> toULength ) {
 const char * saveSourceLimit ;
 size_t size_old = args -> converter -> toULength ;
 size_t size_new_maybe_1 = sizeof ( LMBCS ) - size_old ;
 size_t size_new_maybe_2 = args -> sourceLimit - args -> source ;
 size_t size_new = ( size_new_maybe_1 < size_new_maybe_2 ) ? size_new_maybe_1 : size_new_maybe_2 ;
 uprv_memcpy ( LMBCS , args -> converter -> toUBytes , size_old ) ;
 uprv_memcpy ( LMBCS + size_old , args -> source , size_new ) ;
 saveSourceLimit = args -> sourceLimit ;
 args -> source = errSource = LMBCS ;
 args -> sourceLimit = LMBCS + size_old + size_new ;
 savebytes = ( int8_t ) ( size_old + size_new ) ;
 uniChar = ( UChar ) _LMBCSGetNextUCharWorker ( args , err ) ;
 args -> source = saveSource + ( ( args -> source - LMBCS ) - size_old ) ;
 args -> sourceLimit = saveSourceLimit ;
 if ( * err == U_TRUNCATED_CHAR_FOUND ) {
 args -> converter -> toULength = savebytes ;
 uprv_memcpy ( args -> converter -> toUBytes , LMBCS , savebytes ) ;
 args -> source = args -> sourceLimit ;
 * err = U_ZERO_ERROR ;
 return ;
 }
 else {
 args -> converter -> toULength = 0 ;
 }
 }
 else {
 errSource = saveSource ;
 uniChar = ( UChar ) _LMBCSGetNextUCharWorker ( args , err ) ;
 savebytes = ( int8_t ) ( args -> source - saveSource ) ;
 }
 if ( U_SUCCESS ( * err ) ) {
 if ( uniChar < 0xfffe ) {
 * ( args -> target ) ++ = uniChar ;
 if ( args -> offsets ) {
 * ( args -> offsets ) ++ = ( int32_t ) ( saveSource - pStartLMBCS ) ;
 }
 }
 else if ( uniChar == 0xfffe ) {
 * err = U_INVALID_CHAR_FOUND ;
 }
 else {
 * err = U_ILLEGAL_CHAR_FOUND ;
 }
 }
 }
 if ( U_SUCCESS ( * err ) && args -> sourceLimit > args -> source && args -> targetLimit <= args -> target ) {
 * err = U_BUFFER_OVERFLOW_ERROR ;
 }
 else if ( U_FAILURE ( * err ) ) {
 args -> converter -> toULength = savebytes ;
 if ( savebytes > 0 ) {
 uprv_memcpy ( args -> converter -> toUBytes , errSource , savebytes ) ;
 }
 if ( * err == U_TRUNCATED_CHAR_FOUND ) {
 * err = U_ZERO_ERROR ;
 }
 }
 }