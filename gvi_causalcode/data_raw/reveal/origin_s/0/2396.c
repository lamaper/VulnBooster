void xmlListMerge ( xmlListPtr l1 , xmlListPtr l2 ) {
 xmlListCopy ( l1 , l2 ) ;
 xmlListClear ( l2 ) ;
 }