void * xmlListReverseSearch ( xmlListPtr l , void * data ) {
 xmlLinkPtr lk ;
 if ( l == NULL ) return ( NULL ) ;
 lk = xmlListLinkReverseSearch ( l , data ) ;
 if ( lk ) return ( lk -> data ) ;
 return NULL ;
 }