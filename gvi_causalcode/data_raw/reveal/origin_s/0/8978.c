static void uprint ( const UChar * s , int32_t sourceLen , FILE * f , UErrorCode * status ) {
 UConverter * converter ;
 char buf [ BUF_SIZE ] ;
 const UChar * mySource ;
 const UChar * mySourceEnd ;
 char * myTarget ;
 int32_t arraySize ;
 if ( s == 0 ) return ;
 mySource = s ;
 mySourceEnd = mySource + sourceLen ;
 myTarget = buf ;
 arraySize = BUF_SIZE ;
 converter = ucnv_open ( 0 , status ) ;
 if ( U_FAILURE ( * status ) ) goto finish ;
 do {
 * status = U_ZERO_ERROR ;
 ucnv_fromUnicode ( converter , & myTarget , myTarget + arraySize , & mySource , mySourceEnd , NULL , TRUE , status ) ;
 fwrite ( buf , sizeof ( char ) , myTarget - buf , f ) ;
 myTarget = buf ;
 arraySize = BUF_SIZE ;
 }
 while ( * status == U_BUFFER_OVERFLOW_ERROR ) ;
 finish : ucnv_close ( converter ) ;
 }