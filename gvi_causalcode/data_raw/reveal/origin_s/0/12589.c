static void xsltFreeAttrVT ( xsltAttrVTPtr avt ) {
 int i ;
 if ( avt == NULL ) return ;
 if ( avt -> strstart == 1 ) {
 for ( i = 0 ;
 i < avt -> nb_seg ;
 i += 2 ) if ( avt -> segments [ i ] != NULL ) xmlFree ( ( xmlChar * ) avt -> segments [ i ] ) ;
 for ( i = 1 ;
 i < avt -> nb_seg ;
 i += 2 ) xmlXPathFreeCompExpr ( ( xmlXPathCompExprPtr ) avt -> segments [ i ] ) ;
 }
 else {
 for ( i = 0 ;
 i < avt -> nb_seg ;
 i += 2 ) xmlXPathFreeCompExpr ( ( xmlXPathCompExprPtr ) avt -> segments [ i ] ) ;
 for ( i = 1 ;
 i < avt -> nb_seg ;
 i += 2 ) if ( avt -> segments [ i ] != NULL ) xmlFree ( ( xmlChar * ) avt -> segments [ i ] ) ;
 }
 if ( avt -> nsList != NULL ) xmlFree ( avt -> nsList ) ;
 xmlFree ( avt ) ;
 }