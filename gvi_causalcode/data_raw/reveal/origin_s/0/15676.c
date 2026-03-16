int xmlListCopy ( xmlListPtr cur , const xmlListPtr old ) {
 xmlLinkPtr lk ;
 if ( ( old == NULL ) || ( cur == NULL ) ) return ( 1 ) ;
 for ( lk = old -> sentinel -> next ;
 lk != old -> sentinel ;
 lk = lk -> next ) {
 if ( 0 != xmlListInsert ( cur , lk -> data ) ) {
 xmlListDelete ( cur ) ;
 return ( 1 ) ;
 }
 }
 return ( 0 ) ;
 }