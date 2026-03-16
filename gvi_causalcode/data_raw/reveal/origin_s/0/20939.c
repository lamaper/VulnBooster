static void test_evutil_strtoll ( void ) {
 const char * s ;
 char * endptr ;
 setup_test ( "evutil_stroll: " ) ;
 test_ok = 0 ;
 if ( evutil_strtoll ( "5000000000" , NULL , 10 ) != ( ( ev_int64_t ) 5000000 ) * 1000 ) goto err ;
 if ( evutil_strtoll ( "-5000000000" , NULL , 10 ) != ( ( ev_int64_t ) 5000000 ) * - 1000 ) goto err ;
 s = " 99999stuff" ;
 if ( evutil_strtoll ( s , & endptr , 10 ) != ( ev_int64_t ) 99999 ) goto err ;
 if ( endptr != s + 6 ) goto err ;
 if ( evutil_strtoll ( "foo" , NULL , 10 ) != 0 ) goto err ;
 test_ok = 1 ;
 err : cleanup_test ( ) ;
 }