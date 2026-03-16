static xmlLinkPtr xmlListHigherSearch ( xmlListPtr l , void * data ) {
 xmlLinkPtr lk ;
 if ( l == NULL ) return ( NULL ) ;
 for ( lk = l -> sentinel -> prev ;
 lk != l -> sentinel && l -> linkCompare ( lk -> data , data ) > 0 ;
 lk = lk -> prev ) ;
 return lk ;
 }