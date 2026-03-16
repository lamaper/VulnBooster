int xmlListRemoveAll ( xmlListPtr l , void * data ) {
 int count = 0 ;
 if ( l == NULL ) return ( 0 ) ;
 while ( xmlListRemoveFirst ( l , data ) ) count ++ ;
 return count ;
 }