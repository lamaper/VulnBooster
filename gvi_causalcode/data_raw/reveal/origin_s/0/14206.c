UBool pkg_listContains ( CharList * l , const char * str ) {
 for ( ;
 l ;
 l = l -> next ) {
 if ( ! uprv_strcmp ( l -> str , str ) ) {
 return TRUE ;
 }
 }
 return FALSE ;
 }