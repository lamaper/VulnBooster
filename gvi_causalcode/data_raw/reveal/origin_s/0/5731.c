void xmlListPopFront ( xmlListPtr l ) {
 if ( ! xmlListEmpty ( l ) ) xmlLinkDeallocator ( l , l -> sentinel -> next ) ;
 }