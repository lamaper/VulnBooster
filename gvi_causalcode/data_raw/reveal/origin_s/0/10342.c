void xmlListSort ( xmlListPtr l ) {
 xmlListPtr lTemp ;
 if ( l == NULL ) return ;
 if ( xmlListEmpty ( l ) ) return ;
 if ( NULL == ( lTemp = xmlListDup ( l ) ) ) return ;
 xmlListClear ( l ) ;
 xmlListMerge ( l , lTemp ) ;
 xmlListDelete ( lTemp ) ;
 return ;
 }