int xsltCheckRead ( xsltSecurityPrefsPtr sec , xsltTransformContextPtr ctxt , const xmlChar * URL ) {
 int ret ;
 xmlURIPtr uri ;
 xsltSecurityCheck check ;
 uri = xmlParseURI ( ( const char * ) URL ) ;
 if ( uri == NULL ) {
 xsltTransformError ( ctxt , NULL , NULL , "xsltCheckRead: URL parsing failed for %s\n" , URL ) ;
 return ( - 1 ) ;
 }
 if ( ( uri -> scheme == NULL ) || ( xmlStrEqual ( BAD_CAST uri -> scheme , BAD_CAST "file" ) ) ) {
 check = xsltGetSecurityPrefs ( sec , XSLT_SECPREF_READ_FILE ) ;
 if ( check != NULL ) {
 ret = check ( sec , ctxt , uri -> path ) ;
 if ( ret == 0 ) {
 xsltTransformError ( ctxt , NULL , NULL , "Local file read for %s refused\n" , URL ) ;
 xmlFreeURI ( uri ) ;
 return ( 0 ) ;
 }
 }
 }
 else {
 check = xsltGetSecurityPrefs ( sec , XSLT_SECPREF_READ_NETWORK ) ;
 if ( check != NULL ) {
 ret = check ( sec , ctxt , ( const char * ) URL ) ;
 if ( ret == 0 ) {
 xsltTransformError ( ctxt , NULL , NULL , "Network file read for %s refused\n" , URL ) ;
 xmlFreeURI ( uri ) ;
 return ( 0 ) ;
 }
 }
 }
 xmlFreeURI ( uri ) ;
 return ( 1 ) ;
 }