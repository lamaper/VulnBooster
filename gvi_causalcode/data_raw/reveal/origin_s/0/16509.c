static int checktz ( const char * check ) {
 unsigned int i ;
 const struct tzinfo * what ;
 bool found = FALSE ;
 what = tz ;
 for ( i = 0 ;
 i < sizeof ( tz ) / sizeof ( tz [ 0 ] ) ;
 i ++ ) {
 if ( Curl_raw_equal ( check , what -> name ) ) {
 found = TRUE ;
 break ;
 }
 what ++ ;
 }
 return found ? what -> offset * 60 : - 1 ;
 }