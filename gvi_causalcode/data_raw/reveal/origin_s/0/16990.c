static xmlNodeSetPtr exsltMathLowest ( xmlNodeSetPtr ns ) {
 xmlNodeSetPtr ret = xmlXPathNodeSetCreate ( NULL ) ;
 double min , cur ;
 int i ;
 if ( ( ns == NULL ) || ( ns -> nodeNr == 0 ) ) return ( ret ) ;
 min = xmlXPathCastNodeToNumber ( ns -> nodeTab [ 0 ] ) ;
 if ( xmlXPathIsNaN ( min ) ) return ( ret ) ;
 else xmlXPathNodeSetAddUnique ( ret , ns -> nodeTab [ 0 ] ) ;
 for ( i = 1 ;
 i < ns -> nodeNr ;
 i ++ ) {
 cur = xmlXPathCastNodeToNumber ( ns -> nodeTab [ i ] ) ;
 if ( xmlXPathIsNaN ( cur ) ) {
 xmlXPathEmptyNodeSet ( ret ) ;
 return ( ret ) ;
 }
 if ( cur > min ) continue ;
 if ( cur < min ) {
 min = cur ;
 xmlXPathEmptyNodeSet ( ret ) ;
 xmlXPathNodeSetAddUnique ( ret , ns -> nodeTab [ i ] ) ;
 continue ;
 }
 xmlXPathNodeSetAddUnique ( ret , ns -> nodeTab [ i ] ) ;
 }
 return ( ret ) ;
 }