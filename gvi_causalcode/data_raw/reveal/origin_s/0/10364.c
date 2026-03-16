static int checkday ( const char * check , size_t len ) {
 int i ;
 const char * const * what ;
 bool found = FALSE ;
 if ( len > 3 ) what = & weekday [ 0 ] ;
 else what = & Curl_wkday [ 0 ] ;
 for ( i = 0 ;
 i < 7 ;
 i ++ ) {
 if ( Curl_raw_equal ( check , what [ 0 ] ) ) {
 found = TRUE ;
 break ;
 }
 what ++ ;
 }
 return found ? i : - 1 ;
 }