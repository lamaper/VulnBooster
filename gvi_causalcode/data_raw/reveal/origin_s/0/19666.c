static StemInfo * HintsAppend ( StemInfo * to , StemInfo * extra ) {
 StemInfo * h ;
 if ( to == NULL ) return ( extra ) ;
 if ( extra == NULL ) return ( to ) ;
 for ( h = to ;
 h -> next != NULL ;
 h = h -> next ) ;
 h -> next = extra ;
 return ( to ) ;
 }