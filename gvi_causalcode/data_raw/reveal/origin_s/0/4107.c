xsltDocumentPtr xsltFindDocument ( xsltTransformContextPtr ctxt , xmlDocPtr doc ) {
 xsltDocumentPtr ret ;
 if ( ( ctxt == NULL ) || ( doc == NULL ) ) return ( NULL ) ;
 ret = ctxt -> docList ;
 while ( ret != NULL ) {
 if ( ret -> doc == doc ) return ( ret ) ;
 ret = ret -> next ;
 }
 if ( doc == ctxt -> style -> doc ) return ( ctxt -> document ) ;
 return ( NULL ) ;
 }