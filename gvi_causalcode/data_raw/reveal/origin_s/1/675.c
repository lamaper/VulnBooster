int xsltSetCtxtSecurityPrefs ( xsltSecurityPrefsPtr sec , xsltTransformContextPtr ctxt ) {
 if ( ctxt == NULL ) return ( - 1 ) ;
 ctxt -> sec = ( void * ) sec ;
 return ( 0 ) ;
 }