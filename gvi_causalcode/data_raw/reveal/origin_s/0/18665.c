static xmlLinkPtr xmlListLinkSearch ( xmlListPtr l , void * data ) {
 xmlLinkPtr lk ;
 if ( l == NULL ) return ( NULL ) ;
 lk = xmlListLowerSearch ( l , data ) ;
 if ( lk == l -> sentinel ) return NULL ;
 else {
 if ( l -> linkCompare ( lk -> data , data ) == 0 ) return lk ;
 return NULL ;
 }
 }