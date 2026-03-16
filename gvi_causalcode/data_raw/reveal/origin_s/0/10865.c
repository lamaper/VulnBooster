void virLogOutputListFree ( virLogOutputPtr * list , int count ) {
 size_t i ;
 if ( ! list || count < 0 ) return ;
 for ( i = 0 ;
 i < count ;
 i ++ ) virLogOutputFree ( list [ i ] ) ;
 VIR_FREE ( list ) ;
 }