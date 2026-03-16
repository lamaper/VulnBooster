static void exsltMathLowestFunction ( xmlXPathParserContextPtr ctxt , int nargs ) {
 xmlNodeSetPtr ns , ret ;
 void * user = NULL ;
 if ( nargs != 1 ) {
 xmlXPathSetArityError ( ctxt ) ;
 return ;
 }
 if ( ( ctxt -> value != NULL ) && ( ctxt -> value -> boolval != 0 ) ) {
 user = ctxt -> value -> user ;
 ctxt -> value -> boolval = 0 ;
 ctxt -> value -> user = NULL ;
 }
 ns = xmlXPathPopNodeSet ( ctxt ) ;
 if ( xmlXPathCheckError ( ctxt ) ) return ;
 ret = exsltMathLowest ( ns ) ;
 xmlXPathFreeNodeSet ( ns ) ;
 if ( user != NULL ) xmlFreeNodeList ( ( xmlNodePtr ) user ) ;
 xmlXPathReturnNodeSet ( ctxt , ret ) ;
 }