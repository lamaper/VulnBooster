xsltLocaleChar * xsltStrxfrm ( xsltLocale locale , const xmlChar * string ) {


 xsltLocaleChar * xstr ;

 xstr = ( xsltLocaleChar * ) xmlMalloc ( xstrlen ) ;
 if ( xstr == NULL ) {
 xsltTransformError ( NULL , NULL , NULL , "xsltStrxfrm : out of memory error\n" ) ;
 return ( NULL ) ;
 }
 r = strxfrm_l ( ( char * ) xstr , ( const char * ) string , xstrlen , locale ) ;

 if ( xstrlen == 0 ) {
 xsltTransformError ( NULL , NULL , NULL , "xsltStrxfrm : MultiByteToWideChar check failed\n" ) ;
 return ( NULL ) ;
 }
 xstr = ( xsltLocaleChar * ) xmlMalloc ( xstrlen * sizeof ( xsltLocaleChar ) ) ;
 if ( xstr == NULL ) {
 xsltTransformError ( NULL , NULL , NULL , "xsltStrxfrm : out of memory\n" ) ;
 return ( NULL ) ;
 }
 r = MultiByteToWideChar ( CP_UTF8 , 0 , string , - 1 , xstr , xstrlen ) ;
 if ( r == 0 ) {
 xsltTransformError ( NULL , NULL , NULL , "xsltStrxfrm : MultiByteToWideChar failed\n" ) ;
 xmlFree ( xstr ) ;
 return ( NULL ) ;
 }
 return ( xstr ) ;

 xsltTransformError ( NULL , NULL , NULL , "xsltStrxfrm : strxfrm failed\n" ) ;
 xmlFree ( xstr ) ;
 return ( NULL ) ;
 }
 return ( xstr ) ;
