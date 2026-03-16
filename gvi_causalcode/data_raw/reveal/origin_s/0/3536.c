static struct pskeyval * lookup ( struct pskeydict * dict , char * tokbuf ) {
 int i ;
 for ( i = 0 ;
 i < dict -> cnt ;
 ++ i ) if ( strcmp ( dict -> entries [ i ] . key , tokbuf ) == 0 ) return ( & dict -> entries [ i ] ) ;
 return ( NULL ) ;
 }