xmlChar * xsltEvalAVT ( xsltTransformContextPtr ctxt , void * avt , xmlNodePtr node ) {
 xmlChar * ret = NULL , * tmp ;
 xmlXPathCompExprPtr comp ;
 xsltAttrVTPtr cur = ( xsltAttrVTPtr ) avt ;
 int i ;
 int str ;
 if ( ( ctxt == NULL ) || ( avt == NULL ) || ( node == NULL ) ) return ( NULL ) ;
 str = cur -> strstart ;
 for ( i = 0 ;
 i < cur -> nb_seg ;
 i ++ ) {
 if ( str ) {
 ret = xmlStrcat ( ret , ( const xmlChar * ) cur -> segments [ i ] ) ;
 }
 else {
 comp = ( xmlXPathCompExprPtr ) cur -> segments [ i ] ;
 tmp = xsltEvalXPathStringNs ( ctxt , comp , cur -> nsNr , cur -> nsList ) ;
 if ( tmp != NULL ) {
 if ( ret != NULL ) {
 ret = xmlStrcat ( ret , tmp ) ;
 xmlFree ( tmp ) ;
 }
 else {
 ret = tmp ;
 }
 }
 }
 str = ! str ;
 }
 return ( ret ) ;
 }