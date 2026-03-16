void xsltSetLoaderFunc ( xsltDocLoaderFunc f ) {
 if ( f == NULL ) xsltDocDefaultLoader = xsltDocDefaultLoaderFunc ;
 else xsltDocDefaultLoader = f ;
 }