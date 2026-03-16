REGRESSION_TEST ( SDK_API_TSStatCreate ) ( RegressionTest * test , int level , int * pstatus ) {
 const char name [ ] = "regression.test.metric" ;
 int id ;
 TestBox box ( test , pstatus ) ;
 box = REGRESSION_TEST_PASSED ;
 if ( TSStatFindName ( name , & id ) == TS_SUCCESS ) {
 box . check ( id >= 0 , "TSStatFind(%s) failed with bogus ID %d" , name , id ) ;
 }
 else {
 id = TSStatCreate ( name , TS_RECORDDATATYPE_COUNTER , TS_STAT_NON_PERSISTENT , TS_STAT_SYNC_SUM ) ;
 box . check ( id != TS_ERROR , "TSStatCreate(%s) failed with %d" , name , id ) ;
 }
 TSStatIntSet ( id , getpid ( ) ) ;
 TSStatIntIncrement ( id , 1 ) ;
 TSStatIntIncrement ( id , 1 ) ;
 TSMgmtInt value = TSStatIntGet ( id ) ;
 TSMgmtInt expected = getpid ( ) + 2 ;
 box . check ( expected >= value , "TSStatIntGet(%s) gave %" PRId64 ", expected at least %" PRId64 , name , value , expected ) ;
 }