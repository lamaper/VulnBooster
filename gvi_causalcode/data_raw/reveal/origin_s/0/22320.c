static void exsltMathMaxFunction ( xmlXPathParserContextPtr ctxt , int nargs ) {
 xmlNodeSetPtr ns ;
 double ret ;
 void * user = NULL ;
 if ( nargs != 1 ) {
 xmlXPathSetArityError ( ctxt ) ;
 return ;
 }
 if ( ( ctxt -> value != NULL ) && ( ctxt -> value -> boolval != 0 ) ) {
 user = ctxt -> value -> user ;
 ctxt -> value -> boolval = 0 ;
 ctxt -> value -> user = 0 ;
 }
 ns = xmlXPathPopNodeSet ( ctxt ) ;
 if ( xmlXPathCheckError ( ctxt ) ) return ;
 ret = exsltMathMax ( ns ) ;
 xmlXPathFreeNodeSet ( ns ) ;
 if ( user != NULL ) xmlFreeNodeList ( ( xmlNodePtr ) user ) ;
 xmlXPathReturnNumber ( ctxt , ret ) ;
 }