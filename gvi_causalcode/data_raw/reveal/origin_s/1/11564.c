xmlListPtr xmlListDup ( const xmlListPtr old ) {
 xmlListPtr cur ;
 if ( old == NULL ) return ( NULL ) ;
 if ( NULL == ( cur = xmlListCreate ( NULL , old -> linkCompare ) ) ) return ( NULL ) ;
 if ( 0 != xmlListCopy ( cur , old ) ) return NULL ;
 return cur ;
 }