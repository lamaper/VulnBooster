void ufile_fill_uchar_buffer ( UFILE * f ) {
 UErrorCode status ;
 const char * mySource ;
 const char * mySourceEnd ;
 UChar * myTarget ;
 int32_t bufferSize ;
 int32_t maxCPBytes ;
 int32_t bytesRead ;
 int32_t availLength ;
 int32_t dataSize ;
 char charBuffer [ UFILE_CHARBUFFER_SIZE ] ;
 u_localized_string * str ;
 if ( f -> fFile == NULL ) {
 return ;
 }
 str = & f -> str ;
 dataSize = ( int32_t ) ( str -> fLimit - str -> fPos ) ;
 if ( f -> fFileno == 0 && dataSize > 0 ) {
 return ;
 }
 if ( dataSize != 0 ) {
 u_memmove ( f -> fUCBuffer , str -> fPos , dataSize ) ;
 }
 availLength = UFILE_UCHARBUFFER_SIZE - dataSize ;
 maxCPBytes = availLength / ( f -> fConverter != NULL ? ( 2 * ucnv_getMinCharSize ( f -> fConverter ) ) : 1 ) ;
 if ( f -> fFileno == 0 ) {
 char * retStr = fgets ( charBuffer , ufmt_min ( maxCPBytes , UFILE_CHARBUFFER_SIZE ) , f -> fFile ) ;
 bytesRead = ( int32_t ) ( retStr ? uprv_strlen ( charBuffer ) : 0 ) ;
 }
 else {
 bytesRead = ( int32_t ) fread ( charBuffer , sizeof ( char ) , ufmt_min ( maxCPBytes , UFILE_CHARBUFFER_SIZE ) , f -> fFile ) ;
 }
 status = U_ZERO_ERROR ;
 mySource = charBuffer ;
 mySourceEnd = charBuffer + bytesRead ;
 myTarget = f -> fUCBuffer + dataSize ;
 bufferSize = UFILE_UCHARBUFFER_SIZE ;
 if ( f -> fConverter != NULL ) {
 ucnv_toUnicode ( f -> fConverter , & myTarget , f -> fUCBuffer + bufferSize , & mySource , mySourceEnd , NULL , ( UBool ) ( feof ( f -> fFile ) != 0 ) , & status ) ;
 }
 else {
 u_charsToUChars ( mySource , myTarget , bytesRead ) ;
 myTarget += bytesRead ;
 }
 str -> fPos = str -> fBuffer ;
 str -> fLimit = myTarget ;
 }