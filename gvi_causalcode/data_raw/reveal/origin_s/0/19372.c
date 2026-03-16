CharList * pkg_prependToList ( CharList * l , const char * str ) {
 CharList * newList ;
 newList = uprv_malloc ( sizeof ( CharList ) ) ;
 if ( newList == NULL ) {
 return NULL ;
 }
 newList -> str = str ;
 newList -> next = l ;
 return newList ;
 }