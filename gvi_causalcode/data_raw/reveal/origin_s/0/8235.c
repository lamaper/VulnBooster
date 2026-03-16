xsltLocale xsltNewLocale ( const xmlChar * languageTag ) {

 char localeName [ XSLTMAX_LANGTAGLEN + 6 ] ;
 const xmlChar * p = languageTag ;
 const char * region = NULL ;
 char * q = localeName ;
 int i , llen ;
 if ( languageTag == NULL ) return ( NULL ) ;
 for ( i = 0 ;
 i < XSLTMAX_ISO639LANGLEN && ISALPHA ( * p ) ;
 ++ i ) * q ++ = TOLOWER ( * p ++ ) ;
 if ( i == 0 ) return ( NULL ) ;
 llen = i ;
 if ( * p ) {
 if ( * p ++ != '-' ) return ( NULL ) ;
 * q ++ = '_' ;
 for ( i = 0 ;
 i < XSLTMAX_ISO3166CNTRYLEN && ISALPHA ( * p ) ;
 ++ i ) * q ++ = TOUPPER ( * p ++ ) ;
 if ( i == 0 || * p ) return ( NULL ) ;
 memcpy ( q , ".utf8" , 6 ) ;
 locale = newlocale ( LC_COLLATE_MASK , localeName , NULL ) ;
 if ( locale != NULL ) return ( locale ) ;
 q = localeName + llen ;
 }
 memcpy ( q , ".utf8" , 6 ) ;
 locale = newlocale ( LC_COLLATE_MASK , localeName , NULL ) ;
 if ( locale != NULL ) return ( locale ) ;
 if ( llen != 2 ) return ( NULL ) ;
 region = ( char * ) xsltDefaultRegion ( ( xmlChar * ) localeName ) ;
 if ( region == NULL ) return ( NULL ) ;
 q = localeName + llen ;
 * q ++ = '_' ;
 * q ++ = region [ 0 ] ;
 * q ++ = region [ 1 ] ;
 memcpy ( q , ".utf8" , 6 ) ;
 locale = newlocale ( LC_COLLATE_MASK , localeName , NULL ) ;
 return ( locale ) ;

 xsltLocale locale = ( xsltLocale ) 0 ;
 xmlChar localeName [ XSLTMAX_LANGTAGLEN + 1 ] ;
 xmlChar * q = localeName ;
 const xmlChar * p = languageTag ;
 int i , llen ;
 const xmlChar * region = NULL ;
 if ( languageTag == NULL ) goto end ;
 xsltEnumSupportedLocales ( ) ;
 for ( i = 0 ;
 i < XSLTMAX_ISO639LANGLEN && ISALPHA ( * p ) ;
 ++ i ) * q ++ = TOLOWER ( * p ++ ) ;
 if ( i == 0 ) goto end ;
 llen = i ;
 * q ++ = '-' ;
 if ( * p ) {
 if ( * p ++ != '-' ) goto end ;
 for ( i = 0 ;
 i < XSLTMAX_ISO3166CNTRYLEN && ISALPHA ( * p ) ;
 ++ i ) * q ++ = TOUPPER ( * p ++ ) ;
 if ( i == 0 || * p ) goto end ;
 * q = '\0' ;
 locale = xslt_locale_WINAPI ( localeName ) ;
 if ( locale != ( xsltLocale ) 0 ) goto end ;
 }
 region = xsltDefaultRegion ( localeName ) ;
 if ( region == NULL ) goto end ;
 strcpy ( localeName + llen + 1 , region ) ;
 locale = xslt_locale_WINAPI ( localeName ) ;
 end : return ( locale ) ;
 }

