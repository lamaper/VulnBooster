static void exsltMathConstantFunction ( xmlXPathParserContextPtr ctxt , int nargs ) {
 double ret ;
 xmlChar * name ;
 if ( nargs != 2 ) {
 xmlXPathSetArityError ( ctxt ) ;
 return ;
 }
 ret = xmlXPathPopNumber ( ctxt ) ;
 if ( xmlXPathCheckError ( ctxt ) ) return ;
 name = xmlXPathPopString ( ctxt ) ;
 if ( xmlXPathCheckError ( ctxt ) ) return ;
 ret = exsltMathConstant ( name , ret ) ;
 if ( name != NULL ) xmlFree ( name ) ;
 xmlXPathReturnNumber ( ctxt , ret ) ;
 }