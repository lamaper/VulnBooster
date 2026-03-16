static xmlLinkPtr xmlListLowerSearch ( xmlListPtr l , void * data ) {
 xmlLinkPtr lk ;
 if ( l == NULL ) return ( NULL ) ;
 for ( lk = l -> sentinel -> next ;
 lk != l -> sentinel && l -> linkCompare ( lk -> data , data ) < 0 ;
 lk = lk -> next ) ;
 return lk ;
 }