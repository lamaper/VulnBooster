void xmlListDelete ( xmlListPtr l ) {
 if ( l == NULL ) return ;
 xmlListClear ( l ) ;
 xmlFree ( l -> sentinel ) ;
 xmlFree ( l ) ;
 }