static RefChar * revrefs ( RefChar * cur ) {
 RefChar * p , * n ;
 if ( cur == NULL ) return ( NULL ) ;
 p = NULL ;
 for ( ;
 ( n = cur -> next ) != NULL ;
 cur = n ) {
 cur -> next = p ;
 p = cur ;
 }
 cur -> next = p ;
 return ( cur ) ;
 }