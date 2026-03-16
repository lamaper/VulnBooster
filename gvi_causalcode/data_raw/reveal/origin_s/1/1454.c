xmlChar * xsltEvalAttrValueTemplate ( xsltTransformContextPtr ctxt , xmlNodePtr inst , const xmlChar * name , const xmlChar * ns ) {
 xmlChar * ret ;
 xmlChar * expr ;
 if ( ( ctxt == NULL ) || ( inst == NULL ) || ( name == NULL ) ) return ( NULL ) ;
 expr = xsltGetNsProp ( inst , name , ns ) ;
 if ( expr == NULL ) return ( NULL ) ;
 ret = xsltAttrTemplateValueProcessNode ( ctxt , expr , inst ) ;


 return ( ret ) ;
 }