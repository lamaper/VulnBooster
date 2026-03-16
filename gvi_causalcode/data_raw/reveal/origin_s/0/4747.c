xsltSecurityCheck xsltGetSecurityPrefs ( xsltSecurityPrefsPtr sec , xsltSecurityOption option ) {
 if ( sec == NULL ) return ( NULL ) ;
 switch ( option ) {
 case XSLT_SECPREF_READ_FILE : return ( sec -> readFile ) ;
 case XSLT_SECPREF_WRITE_FILE : return ( sec -> createFile ) ;
 case XSLT_SECPREF_CREATE_DIRECTORY : return ( sec -> createDir ) ;
 case XSLT_SECPREF_READ_NETWORK : return ( sec -> readNet ) ;
 case XSLT_SECPREF_WRITE_NETWORK : return ( sec -> writeNet ) ;
 }
 return ( NULL ) ;
 }