static void prepare_dummy_password ( char * buf , size_t sz ) {
 size_t i ;
 strlcpy ( buf , "6F a[" , sz ) ;
 for ( i = strlen ( buf ) ;
 i < sz - 1 ;
 i ++ ) buf [ i ] = 'a' + ( i % 26 ) ;
 buf [ sz - 1 ] = '\0' ;
 }