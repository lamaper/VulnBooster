static unsigned int hashname ( const char * name ) {
 unsigned int hash = 0 ;
 while ( * name ) {
 unsigned int extra = ( hash >> 27 ) ;
 hash <<= 5 ;
 hash += * name & 0x1f ;
 hash ^= extra ;
 ++ name ;
 }
 return ( hash % 257 ) ;
 }