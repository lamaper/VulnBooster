void xsltFreeDocuments ( xsltTransformContextPtr ctxt ) {
 xsltDocumentPtr doc , cur ;
 cur = ctxt -> docList ;
 while ( cur != NULL ) {
 doc = cur ;
 cur = cur -> next ;
 xsltFreeDocumentKeys ( doc ) ;
 if ( ! doc -> main ) xmlFreeDoc ( doc -> doc ) ;
 xmlFree ( doc ) ;
 }
 cur = ctxt -> styleList ;
 while ( cur != NULL ) {
 doc = cur ;
 cur = cur -> next ;
 xsltFreeDocumentKeys ( doc ) ;
 if ( ! doc -> main ) xmlFreeDoc ( doc -> doc ) ;
 xmlFree ( doc ) ;
 }
 }