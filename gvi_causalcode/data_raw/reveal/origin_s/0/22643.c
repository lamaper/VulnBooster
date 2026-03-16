static int xsltCheckWritePath ( xsltSecurityPrefsPtr sec , xsltTransformContextPtr ctxt , const char * path ) {
 int ret ;
 xsltSecurityCheck check ;
 char * directory ;
 check = xsltGetSecurityPrefs ( sec , XSLT_SECPREF_WRITE_FILE ) ;
 if ( check != NULL ) {
 ret = check ( sec , ctxt , path ) ;
 if ( ret == 0 ) {
 xsltTransformError ( ctxt , NULL , NULL , "File write for %s refused\n" , path ) ;
 return ( 0 ) ;
 }
 }
 directory = xmlParserGetDirectory ( path ) ;
 if ( directory != NULL ) {
 ret = xsltCheckFilename ( directory ) ;
 if ( ret == 0 ) {
 check = xsltGetSecurityPrefs ( sec , XSLT_SECPREF_CREATE_DIRECTORY ) ;
 if ( check != NULL ) {
 ret = check ( sec , ctxt , directory ) ;
 if ( ret == 0 ) {
 xsltTransformError ( ctxt , NULL , NULL , "Directory creation for %s refused\n" , path ) ;
 xmlFree ( directory ) ;
 return ( 0 ) ;
 }
 }
 ret = xsltCheckWritePath ( sec , ctxt , directory ) ;
 if ( ret == 1 ) ret = mkdir ( directory , 0755 ) ;
 }
 xmlFree ( directory ) ;
 if ( ret < 0 ) return ( ret ) ;
 }
 return ( 1 ) ;
 }