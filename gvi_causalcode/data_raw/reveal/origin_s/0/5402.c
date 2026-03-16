xsltSecurityPrefsPtr xsltNewSecurityPrefs ( void ) {
 xsltSecurityPrefsPtr ret ;
 xsltInitGlobals ( ) ;
 ret = ( xsltSecurityPrefsPtr ) xmlMalloc ( sizeof ( xsltSecurityPrefs ) ) ;
 if ( ret == NULL ) {
 xsltTransformError ( NULL , NULL , NULL , "xsltNewSecurityPrefs : malloc failed\n" ) ;
 return ( NULL ) ;
 }
 memset ( ret , 0 , sizeof ( xsltSecurityPrefs ) ) ;
 return ( ret ) ;
 }