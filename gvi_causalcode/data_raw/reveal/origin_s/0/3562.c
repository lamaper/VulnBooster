void xmlListClear ( xmlListPtr l ) {
 xmlLinkPtr lk ;
 if ( l == NULL ) return ;
 lk = l -> sentinel -> next ;
 while ( lk != l -> sentinel ) {
 xmlLinkPtr next = lk -> next ;
 xmlLinkDeallocator ( l , lk ) ;
 lk = next ;
 }
 }