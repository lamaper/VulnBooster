xmlChar * xsltEvalXPathString ( xsltTransformContextPtr ctxt , xmlXPathCompExprPtr comp ) {
 return ( xsltEvalXPathStringNs ( ctxt , comp , 0 , NULL ) ) ;
 }