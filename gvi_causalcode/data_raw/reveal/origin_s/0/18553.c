int xsltSetSecurityPrefs ( xsltSecurityPrefsPtr sec , xsltSecurityOption option , xsltSecurityCheck func ) {
 xsltInitGlobals ( ) ;
 if ( sec == NULL ) return ( - 1 ) ;
 switch ( option ) {
 case XSLT_SECPREF_READ_FILE : sec -> readFile = func ;
 return ( 0 ) ;
 case XSLT_SECPREF_WRITE_FILE : sec -> createFile = func ;
 return ( 0 ) ;
 case XSLT_SECPREF_CREATE_DIRECTORY : sec -> createDir = func ;
 return ( 0 ) ;
 case XSLT_SECPREF_READ_NETWORK : sec -> readNet = func ;
 return ( 0 ) ;
 case XSLT_SECPREF_WRITE_NETWORK : sec -> writeNet = func ;
 return ( 0 ) ;
 }
 return ( - 1 ) ;
 }