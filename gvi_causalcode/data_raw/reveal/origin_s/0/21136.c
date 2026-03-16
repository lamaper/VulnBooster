void xsltFreeSecurityPrefs ( xsltSecurityPrefsPtr sec ) {
 if ( sec == NULL ) return ;
 xmlFree ( sec ) ;
 }