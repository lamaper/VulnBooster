xmlChar * xsltEvalXPathStringNs ( xsltTransformContextPtr ctxt , xmlXPathCompExprPtr comp , int nsNr , xmlNsPtr * nsList ) {
 xmlChar * ret = NULL ;
 xmlXPathObjectPtr res ;
 xmlNodePtr oldInst ;
 xmlNodePtr oldNode ;
 int oldPos , oldSize ;
 int oldNsNr ;
 xmlNsPtr * oldNamespaces ;
 oldInst = ctxt -> inst ;
 oldNode = ctxt -> node ;
 oldPos = ctxt -> xpathCtxt -> proximityPosition ;
 oldSize = ctxt -> xpathCtxt -> contextSize ;
 oldNsNr = ctxt -> xpathCtxt -> nsNr ;
 oldNamespaces = ctxt -> xpathCtxt -> namespaces ;
 ctxt -> xpathCtxt -> node = ctxt -> node ;
 ctxt -> xpathCtxt -> namespaces = nsList ;
 ctxt -> xpathCtxt -> nsNr = nsNr ;
 res = xmlXPathCompiledEval ( comp , ctxt -> xpathCtxt ) ;
 if ( res != NULL ) {
 if ( res -> type != XPATH_STRING ) res = xmlXPathConvertString ( res ) ;
 if ( res -> type == XPATH_STRING ) {
 ret = res -> stringval ;
 res -> stringval = NULL ;
 }
 else {
 xsltTransformError ( ctxt , NULL , NULL , "xpath : string() function didn't return a String\n" ) ;
 }
 xmlXPathFreeObject ( res ) ;
 }
 else {
 ctxt -> state = XSLT_STATE_STOPPED ;
 }


 ctxt -> node = oldNode ;
 ctxt -> xpathCtxt -> contextSize = oldSize ;
 ctxt -> xpathCtxt -> proximityPosition = oldPos ;
 ctxt -> xpathCtxt -> nsNr = oldNsNr ;
 ctxt -> xpathCtxt -> namespaces = oldNamespaces ;
 return ( ret ) ;
 }