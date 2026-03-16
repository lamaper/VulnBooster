xmlChar * xsltEvalTemplateString ( xsltTransformContextPtr ctxt , xmlNodePtr contextNode , xmlNodePtr inst ) {
 xmlNodePtr oldInsert , insert = NULL ;
 xmlChar * ret ;
 if ( ( ctxt == NULL ) || ( contextNode == NULL ) || ( inst == NULL ) ) return ( NULL ) ;
 if ( inst -> children == NULL ) return ( NULL ) ;
 insert = xmlNewDocNode ( ctxt -> output , NULL , ( const xmlChar * ) "fake" , NULL ) ;
 if ( insert == NULL ) {
 xsltTransformError ( ctxt , NULL , contextNode , "Failed to create temporary node\n" ) ;
 return ( NULL ) ;
 }
 oldInsert = ctxt -> insert ;
 ctxt -> insert = insert ;
 xsltApplyOneTemplate ( ctxt , contextNode , inst -> children , NULL , NULL ) ;
 ctxt -> insert = oldInsert ;
 ret = xmlNodeGetContent ( insert ) ;
 if ( insert != NULL ) xmlFreeNode ( insert ) ;
 return ( ret ) ;
 }