static xmlNodeSetPtr exsltMathHighest ( xmlNodeSetPtr ns ) {
 xmlNodeSetPtr ret = xmlXPathNodeSetCreate ( NULL ) ;
 double max , cur ;
 int i ;
 if ( ( ns == NULL ) || ( ns -> nodeNr == 0 ) ) return ( ret ) ;
 max = xmlXPathCastNodeToNumber ( ns -> nodeTab [ 0 ] ) ;
 if ( xmlXPathIsNaN ( max ) ) return ( ret ) ;
 else xmlXPathNodeSetAddUnique ( ret , ns -> nodeTab [ 0 ] ) ;
 for ( i = 1 ;
 i < ns -> nodeNr ;
 i ++ ) {
 cur = xmlXPathCastNodeToNumber ( ns -> nodeTab [ i ] ) ;
 if ( xmlXPathIsNaN ( cur ) ) {
 xmlXPathEmptyNodeSet ( ret ) ;
 return ( ret ) ;
 }
 if ( cur < max ) continue ;
 if ( cur > max ) {
 max = cur ;
 xmlXPathEmptyNodeSet ( ret ) ;
 xmlXPathNodeSetAddUnique ( ret , ns -> nodeTab [ i ] ) ;
 continue ;
 }
 xmlXPathNodeSetAddUnique ( ret , ns -> nodeTab [ i ] ) ;
 }
 return ( ret ) ;
 }