REGRESSION_TEST ( SDK_API_TSCache ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 SDK_Cache_test = test ;
 SDK_Cache_pstatus = pstatus ;
 int is_ready = 0 ;
 TSCacheReady ( & is_ready ) ;
 if ( ! is_ready ) {
 SDK_RPRINT ( test , "TSCacheReady" , "TestCase1" , TC_FAIL , "cache is not ready" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSCacheReady" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 char key_name [ ] = "key_for_regression_test" ;
 TSCacheKey key = TSCacheKeyCreate ( ) ;
 TSCacheKey key_cmp = TSCacheKeyCreate ( ) ;
 SDK_RPRINT ( test , "TSCacheKeyCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 TSCacheKeyDigestSet ( key , key_name , strlen ( key_name ) ) ;
 TSCacheKeyDigestSet ( key_cmp , key_name , strlen ( key_name ) ) ;

 SDK_RPRINT ( test , "TSCacheKeySetDigest" , "TestCase1" , TC_FAIL , "digest is wrong" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 TSCacheKeyDestroy ( key ) ;
 TSCacheKeyDestroy ( key_cmp ) ;
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSCacheKeySetDigest" , "TestCase1" , TC_PASS , "ok" ) ;
 TSCacheKeyDestroy ( key_cmp ) ;
 }

 i < ( OBJECT_SIZE - 1 ) ;
 i ++ ) {
 content [ i ] = 'a' ;
 }
 content [ OBJECT_SIZE - 1 ] = '\0' ;
 TSCont contp = TSContCreate ( cache_handler , TSMutexCreate ( ) ) ;
 CacheVConnStruct * cache_vconn = ( CacheVConnStruct * ) TSmalloc ( sizeof ( CacheVConnStruct ) ) ;
 cache_vconn -> key = key ;
 TSContDataSet ( contp , cache_vconn ) ;
 TSCacheWrite ( contp , key ) ;
 }