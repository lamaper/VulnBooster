int test ( char * URL ) {
 int i ;
 ( void ) URL ;
 for ( i = 0 ;
 dates [ i ] ;
 i ++ ) {
 printf ( "%d: %s => %ld\n" , i , dates [ i ] , ( long ) curl_getdate ( dates [ i ] , NULL ) ) ;
 }
 return 0 ;
 }