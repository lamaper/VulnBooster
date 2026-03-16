uint32_t pkg_countCharList ( CharList * l ) {
 uint32_t c = 0 ;
 while ( l != NULL ) {
 c ++ ;
 l = l -> next ;
 }
 return c ;
 }