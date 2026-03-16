int xmlListRemoveLast ( xmlListPtr l , void * data ) {
 xmlLinkPtr lk ;
 if ( l == NULL ) return ( 0 ) ;
 lk = xmlListLinkReverseSearch ( l , data ) ;
 if ( lk != NULL ) {
 xmlLinkDeallocator ( l , lk ) ;
 return 1 ;
 }
 return 0 ;
 }