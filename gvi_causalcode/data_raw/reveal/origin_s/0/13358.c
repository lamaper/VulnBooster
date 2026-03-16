xsltDocumentPtr xsltNewDocument ( xsltTransformContextPtr ctxt , xmlDocPtr doc ) {
 xsltDocumentPtr cur ;
 cur = ( xsltDocumentPtr ) xmlMalloc ( sizeof ( xsltDocument ) ) ;
 if ( cur == NULL ) {
 xsltTransformError ( ctxt , NULL , ( xmlNodePtr ) doc , "xsltNewDocument : malloc failed\n" ) ;
 return ( NULL ) ;
 }
 memset ( cur , 0 , sizeof ( xsltDocument ) ) ;
 cur -> doc = doc ;
 if ( ctxt != NULL ) {
 if ( ! XSLT_IS_RES_TREE_FRAG ( doc ) ) {
 cur -> next = ctxt -> docList ;
 ctxt -> docList = cur ;
 }
 }
 return ( cur ) ;
 }