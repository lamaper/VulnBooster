static double exsltMathMax ( xmlNodeSetPtr ns ) {
 double ret , cur ;
 int i ;
 if ( ( ns == NULL ) || ( ns -> nodeNr == 0 ) ) return ( xmlXPathNAN ) ;
 ret = xmlXPathCastNodeToNumber ( ns -> nodeTab [ 0 ] ) ;
 if ( xmlXPathIsNaN ( ret ) ) return ( xmlXPathNAN ) ;
 for ( i = 1 ;
 i < ns -> nodeNr ;
 i ++ ) {
 cur = xmlXPathCastNodeToNumber ( ns -> nodeTab [ i ] ) ;
 if ( xmlXPathIsNaN ( cur ) ) return ( xmlXPathNAN ) ;
 if ( cur > ret ) ret = cur ;
 }
 return ( ret ) ;
 }