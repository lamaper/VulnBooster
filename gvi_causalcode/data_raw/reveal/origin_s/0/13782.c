void xmlListPopBack ( xmlListPtr l ) {
 if ( ! xmlListEmpty ( l ) ) xmlLinkDeallocator ( l , l -> sentinel -> prev ) ;
 }