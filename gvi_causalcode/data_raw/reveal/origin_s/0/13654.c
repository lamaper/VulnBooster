static xsltAttrVTPtr xsltNewAttrVT ( xsltStylesheetPtr style ) {
 xsltAttrVTPtr cur ;
 cur = ( xsltAttrVTPtr ) xmlMalloc ( sizeof ( xsltAttrVT ) ) ;
 if ( cur == NULL ) {
 xsltTransformError ( NULL , style , NULL , "xsltNewAttrVTPtr : malloc failed\n" ) ;
 if ( style != NULL ) style -> errors ++ ;
 return ( NULL ) ;
 }
 memset ( cur , 0 , sizeof ( xsltAttrVT ) ) ;
 cur -> nb_seg = 0 ;
 cur -> max_seg = MAX_AVT_SEG ;
 cur -> strstart = 0 ;
 cur -> next = style -> attVTs ;
 style -> attVTs = ( xsltAttrVTPtr ) cur ;
 return ( cur ) ;
 }