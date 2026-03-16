const xmlChar * xsltEvalStaticAttrValueTemplate ( xsltStylesheetPtr style , xmlNodePtr inst , const xmlChar * name , const xmlChar * ns , int * found ) {
 const xmlChar * ret ;
 xmlChar * expr ;
 if ( ( style == NULL ) || ( inst == NULL ) || ( name == NULL ) ) return ( NULL ) ;
 expr = xsltGetNsProp ( inst , name , ns ) ;
 if ( expr == NULL ) {
 * found = 0 ;
 return ( NULL ) ;
 }
 * found = 1 ;
 ret = xmlStrchr ( expr , '{
' ) ;
 if ( ret != NULL ) {
 xmlFree ( expr ) ;
 return ( NULL ) ;
 }
 ret = xmlDictLookup ( style -> dict , expr , - 1 ) ;
 xmlFree ( expr ) ;
 return ( ret ) ;
 }