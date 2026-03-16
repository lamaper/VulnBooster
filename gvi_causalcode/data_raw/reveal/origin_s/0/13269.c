static void xmlLinkDeallocator ( xmlListPtr l , xmlLinkPtr lk ) {
 ( lk -> prev ) -> next = lk -> next ;
 ( lk -> next ) -> prev = lk -> prev ;
 if ( l -> linkDeallocator ) l -> linkDeallocator ( lk ) ;
 xmlFree ( lk ) ;
 }