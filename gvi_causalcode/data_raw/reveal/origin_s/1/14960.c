xsltDocumentPtr xsltNewStyleDocument ( xsltStylesheetPtr style , xmlDocPtr doc ) {
 xsltDocumentPtr cur ;
 cur = ( xsltDocumentPtr ) xmlMalloc ( sizeof ( xsltDocument ) ) ;
 if ( cur == NULL ) {
 xsltTransformError ( NULL , style , ( xmlNodePtr ) doc , "xsltNewStyleDocument : malloc failed\n" ) ;
 return ( NULL ) ;
 }
 memset ( cur , 0 , sizeof ( xsltDocument ) ) ;
 cur -> doc = doc ;
 if ( style != NULL ) {
 cur -> next = style -> docList ;
 style -> docList = cur ;
 }
 return ( cur ) ;
 }