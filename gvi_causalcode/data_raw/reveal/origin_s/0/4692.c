static struct taboff * findtabindir ( struct tabdir * td , uint32 tag ) {
 int i ;
 for ( i = 0 ;
 i < td -> numtab ;
 ++ i ) if ( td -> tabs [ i ] . tag == tag ) return ( & td -> tabs [ i ] ) ;
 return ( NULL ) ;
 }