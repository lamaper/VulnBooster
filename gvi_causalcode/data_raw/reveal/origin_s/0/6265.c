static void exsltSaxonEvalFunction ( xmlXPathParserContextPtr ctxt , int nargs ) {
 xmlXPathCompExprPtr expr ;
 xmlXPathObjectPtr ret ;
 if ( nargs != 1 ) {
 xmlXPathSetArityError ( ctxt ) ;
 return ;
 }
 if ( ! xmlXPathStackIsExternal ( ctxt ) ) {
 xmlXPathSetTypeError ( ctxt ) ;
 return ;
 }
 expr = ( xmlXPathCompExprPtr ) xmlXPathPopExternal ( ctxt ) ;
 ret = xmlXPathCompiledEval ( expr , ctxt -> context ) ;
 valuePush ( ctxt , ret ) ;
 }