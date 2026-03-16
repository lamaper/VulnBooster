int xmlListEmpty ( xmlListPtr l ) {
 if ( l == NULL ) return ( - 1 ) ;
 return ( l -> sentinel -> next == l -> sentinel ) ;
 }