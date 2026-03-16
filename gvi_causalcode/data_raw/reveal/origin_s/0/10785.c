int xmlListSize ( xmlListPtr l ) {
 xmlLinkPtr lk ;
 int count = 0 ;
 if ( l == NULL ) return ( - 1 ) ;
 for ( lk = l -> sentinel -> next ;
 lk != l -> sentinel ;
 lk = lk -> next , count ++ ) ;
 return count ;
 }