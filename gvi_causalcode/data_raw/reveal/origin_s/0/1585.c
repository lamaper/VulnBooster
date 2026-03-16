void * xmlListSearch ( xmlListPtr l , void * data ) {
 xmlLinkPtr lk ;
 if ( l == NULL ) return ( NULL ) ;
 lk = xmlListLinkSearch ( l , data ) ;
 if ( lk ) return ( lk -> data ) ;
 return NULL ;
 }