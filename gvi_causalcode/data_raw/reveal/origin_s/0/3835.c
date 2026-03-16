static void exsltMathMinFunction ( xmlXPathParserContextPtr ctxt , int nargs ) {
 xmlNodeSetPtr ns ;
 double ret ;
 void * user = NULL ;
 if ( nargs != 1 ) {
 xsltGenericError ( xsltGenericErrorContext , "math:min: invalid number of arguments\n" ) ;
 ctxt -> error = XPATH_INVALID_ARITY ;
 return ;
 }
 if ( ( ctxt -> value != NULL ) && ( ctxt -> value -> boolval != 0 ) ) {
 user = ctxt -> value -> user ;
 ctxt -> value -> boolval = 0 ;
 ctxt -> value -> user = NULL ;
 }
 ns = xmlXPathPopNodeSet ( ctxt ) ;
 if ( xmlXPathCheckError ( ctxt ) ) return ;
 ret = exsltMathMin ( ns ) ;
 xmlXPathFreeNodeSet ( ns ) ;
 if ( user != NULL ) xmlFreeNodeList ( ( xmlNodePtr ) user ) ;
 xmlXPathReturnNumber ( ctxt , ret ) ;
 }