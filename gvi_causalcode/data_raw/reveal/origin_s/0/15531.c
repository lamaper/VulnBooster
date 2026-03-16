void xmlListReverse ( xmlListPtr l ) {
 xmlLinkPtr lk ;
 xmlLinkPtr lkPrev ;
 if ( l == NULL ) return ;
 lkPrev = l -> sentinel ;
 for ( lk = l -> sentinel -> next ;
 lk != l -> sentinel ;
 lk = lk -> next ) {
 lkPrev -> next = lkPrev -> prev ;
 lkPrev -> prev = lk ;
 lkPrev = lk ;
 }
 lkPrev -> next = lkPrev -> prev ;
 lkPrev -> prev = lk ;
 }