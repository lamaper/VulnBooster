void xsltFreeStyleDocuments ( xsltStylesheetPtr style ) {
 xsltDocumentPtr doc , cur ;



 else nsMap = NULL ;

 while ( cur != NULL ) {
 doc = cur ;
 cur = cur -> next ;


 if ( ! doc -> main ) xmlFreeDoc ( doc -> doc ) ;
 xmlFree ( doc ) ;
 }
 }