static void exsltNodeSetFunction ( xmlXPathParserContextPtr ctxt , int nargs ) {
 if ( nargs != 1 ) {
 xmlXPathSetArityError ( ctxt ) ;
 return ;
 }
 if ( xmlXPathStackIsNodeSet ( ctxt ) ) {
 xsltFunctionNodeSet ( ctxt , nargs ) ;
 return ;
 }
 else {
 xmlDocPtr fragment ;
 xsltTransformContextPtr tctxt = xsltXPathGetTransformContext ( ctxt ) ;
 xmlNodePtr txt ;
 xmlChar * strval ;
 xmlXPathObjectPtr obj ;
 fragment = xsltCreateRVT ( tctxt ) ;
 if ( fragment == NULL ) {
 xsltTransformError ( tctxt , NULL , tctxt -> inst , "exsltNodeSetFunction: Failed to create a tree fragment.\n" ) ;
 tctxt -> state = XSLT_STATE_STOPPED ;
 return ;
 }
 xsltRegisterLocalRVT ( tctxt , fragment ) ;
 strval = xmlXPathPopString ( ctxt ) ;
 txt = xmlNewDocText ( fragment , strval ) ;
 xmlAddChild ( ( xmlNodePtr ) fragment , txt ) ;
 obj = xmlXPathNewNodeSet ( txt ) ;
 if ( obj == NULL ) {
 xsltTransformError ( tctxt , NULL , tctxt -> inst , "exsltNodeSetFunction: Failed to create a node set object.\n" ) ;
 tctxt -> state = XSLT_STATE_STOPPED ;
 }
 else {
 xsltExtensionInstructionResultRegister ( tctxt , obj ) ;
 }
 if ( strval != NULL ) xmlFree ( strval ) ;
 valuePush ( ctxt , obj ) ;
 }
 }