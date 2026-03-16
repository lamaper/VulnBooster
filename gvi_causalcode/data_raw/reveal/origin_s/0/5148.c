static void parseMappings ( const char * filename , UBool reportError , UErrorCode * pErrorCode ) {
 char * fields [ 3 ] [ 2 ] ;
 if ( pErrorCode == NULL || U_FAILURE ( * pErrorCode ) ) {
 return ;
 }
 u_parseDelimitedFile ( filename , ';
' , fields , 3 , strprepProfileLineFn , ( void * ) filename , pErrorCode ) ;
 if ( U_FAILURE ( * pErrorCode ) && ( reportError || * pErrorCode != U_FILE_ACCESS_ERROR ) ) {
 fprintf ( stderr , "gensprep error: u_parseDelimitedFile(\"%s\") failed - %s\n" , filename , u_errorName ( * pErrorCode ) ) ;
 exit ( * pErrorCode ) ;
 }
 }