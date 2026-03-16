xmlLinkPtr xmlListEnd ( xmlListPtr l ) {
 if ( l == NULL ) return ( NULL ) ;
 return ( l -> sentinel -> prev ) ;
 }