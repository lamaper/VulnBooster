xmlLinkPtr xmlListFront ( xmlListPtr l ) {
 if ( l == NULL ) return ( NULL ) ;
 return ( l -> sentinel -> next ) ;
 }