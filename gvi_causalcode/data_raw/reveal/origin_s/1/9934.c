static xmlLinkPtr xmlListLinkReverseSearch ( xmlListPtr l , void * data ) {
 xmlLinkPtr lk ;
 if ( l == NULL ) return ( NULL ) ;
 lk = xmlListHigherSearch ( l , data ) ;
 if ( lk == l -> sentinel ) return NULL ;
 else {
 if ( l -> linkCompare ( lk -> data , data ) == 0 ) return lk ;
 return NULL ;
 }
 }