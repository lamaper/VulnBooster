static void parseNormalizationCorrections ( const char * filename , UErrorCode * pErrorCode ) {
 char * fields [ 4 ] [ 2 ] ;
 if ( pErrorCode == NULL || U_FAILURE ( * pErrorCode ) ) {
 return ;
 }
 u_parseDelimitedFile ( filename , ';
' , fields , 4 , normalizationCorrectionsLineFn , NULL , pErrorCode ) ;
 if ( U_FAILURE ( * pErrorCode ) && ( * pErrorCode != U_FILE_ACCESS_ERROR ) ) {
 fprintf ( stderr , "gensprep error: u_parseDelimitedFile(\"%s\") failed - %s\n" , filename , u_errorName ( * pErrorCode ) ) ;
 exit ( * pErrorCode ) ;
 }
 }