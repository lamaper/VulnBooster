static void exsltSaxonExpressionFunction ( xmlXPathParserContextPtr ctxt , int nargs ) {
 xmlChar * arg ;
 xmlXPathCompExprPtr ret ;
 xmlHashTablePtr hash ;
 xsltTransformContextPtr tctxt = xsltXPathGetTransformContext ( ctxt ) ;
 if ( nargs != 1 ) {
 xmlXPathSetArityError ( ctxt ) ;
 return ;
 }
 arg = xmlXPathPopString ( ctxt ) ;
 if ( xmlXPathCheckError ( ctxt ) || ( arg == NULL ) ) {
 xmlXPathSetTypeError ( ctxt ) ;
 return ;
 }
 hash = ( xmlHashTablePtr ) xsltGetExtData ( tctxt , ctxt -> context -> functionURI ) ;
 ret = xmlHashLookup ( hash , arg ) ;
 if ( ret == NULL ) {
 ret = xmlXPathCompile ( arg ) ;
 if ( ret == NULL ) {
 xmlFree ( arg ) ;
 xsltGenericError ( xsltGenericErrorContext , "{
%s}
:%s: argument is not an XPath expression\n" , ctxt -> context -> functionURI , ctxt -> context -> function ) ;
 return ;
 }
 xmlHashAddEntry ( hash , arg , ( void * ) ret ) ;
 }
 xmlFree ( arg ) ;
 xmlXPathReturnExternal ( ctxt , ret ) ;
 }