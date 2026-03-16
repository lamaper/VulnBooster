static void exsltObjectTypeFunction ( xmlXPathParserContextPtr ctxt , int nargs ) {
 xmlXPathObjectPtr obj , ret ;
 if ( nargs != 1 ) {
 xmlXPathSetArityError ( ctxt ) ;
 return ;
 }
 obj = valuePop ( ctxt ) ;
 switch ( obj -> type ) {
 case XPATH_STRING : ret = xmlXPathNewCString ( "string" ) ;
 break ;
 case XPATH_NUMBER : ret = xmlXPathNewCString ( "number" ) ;
 break ;
 case XPATH_BOOLEAN : ret = xmlXPathNewCString ( "boolean" ) ;
 break ;
 case XPATH_NODESET : ret = xmlXPathNewCString ( "node-set" ) ;
 break ;
 case XPATH_XSLT_TREE : ret = xmlXPathNewCString ( "RTF" ) ;
 break ;
 case XPATH_USERS : ret = xmlXPathNewCString ( "external" ) ;
 break ;
 default : xsltGenericError ( xsltGenericErrorContext , "object-type() invalid arg\n" ) ;
 ctxt -> error = XPATH_INVALID_TYPE ;
 xmlXPathFreeObject ( obj ) ;
 return ;
 }
 xmlXPathFreeObject ( obj ) ;
 valuePush ( ctxt , ret ) ;
 }