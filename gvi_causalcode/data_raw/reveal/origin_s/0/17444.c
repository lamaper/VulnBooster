void virLogFilterListFree ( virLogFilterPtr * list , int count ) {
 size_t i ;
 if ( ! list || count < 0 ) return ;
 for ( i = 0 ;
 i < count ;
 i ++ ) virLogFilterFree ( list [ i ] ) ;
 VIR_FREE ( list ) ;
 }