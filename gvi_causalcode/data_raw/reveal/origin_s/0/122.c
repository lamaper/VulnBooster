void xsltFunctionNodeSet ( xmlXPathParserContextPtr ctxt , int nargs ) {
 if ( nargs != 1 ) {
 xsltTransformError ( xsltXPathGetTransformContext ( ctxt ) , NULL , NULL , "node-set() : expects one result-tree arg\n" ) ;
 ctxt -> error = XPATH_INVALID_ARITY ;
 return ;
 }
 if ( ( ctxt -> value == NULL ) || ( ( ctxt -> value -> type != XPATH_XSLT_TREE ) && ( ctxt -> value -> type != XPATH_NODESET ) ) ) {
 xsltTransformError ( xsltXPathGetTransformContext ( ctxt ) , NULL , NULL , "node-set() invalid arg expecting a result tree\n" ) ;
 ctxt -> error = XPATH_INVALID_TYPE ;
 return ;
 }
 if ( ctxt -> value -> type == XPATH_XSLT_TREE ) {
 ctxt -> value -> type = XPATH_NODESET ;
 }
 }