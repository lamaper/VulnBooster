int xsltCheckWrite ( xsltSecurityPrefsPtr sec , xsltTransformContextPtr ctxt , const xmlChar * URL ) {
 int ret ;
 xmlURIPtr uri ;
 xsltSecurityCheck check ;
 uri = xmlParseURI ( ( const char * ) URL ) ;
 if ( uri == NULL ) {
 uri = xmlCreateURI ( ) ;
 if ( uri == NULL ) {
 xsltTransformError ( ctxt , NULL , NULL , "xsltCheckWrite: out of memory for %s\n" , URL ) ;
 return ( - 1 ) ;
 }
 uri -> path = ( char * ) xmlStrdup ( URL ) ;
 }
 if ( ( uri -> scheme == NULL ) || ( xmlStrEqual ( BAD_CAST uri -> scheme , BAD_CAST "file" ) ) ) {

 else # endif ret = xsltCheckWritePath ( sec , ctxt , uri -> path ) ;
 if ( ret <= 0 ) {
 xmlFreeURI ( uri ) ;
 return ( ret ) ;
 }
 }
 else {
 check = xsltGetSecurityPrefs ( sec , XSLT_SECPREF_WRITE_NETWORK ) ;
 if ( check != NULL ) {
 ret = check ( sec , ctxt , ( const char * ) URL ) ;
 if ( ret == 0 ) {
 xsltTransformError ( ctxt , NULL , NULL , "File write for %s refused\n" , URL ) ;
 xmlFreeURI ( uri ) ;
 return ( 0 ) ;
 }
 }
 }
 xmlFreeURI ( uri ) ;
 return ( 1 ) ;
 }