REGRESSION_TEST ( SDK_API_TXN_HTTP_INFO_GET ) ( RegressionTest * test , int , int * pstatus ) {
 HttpSM * s = HttpSM : : allocate ( ) ;
 bool success = true ;
 TSHttpTxn txnp = reinterpret_cast < TSHttpTxn > ( s ) ;
 TSMgmtInt ival_read ;
 s -> init ( ) ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 HttpCacheSM * c_sm = & ( s -> get_cache_sm ( ) ) ;
 c_sm -> set_readwhilewrite_inprogress ( true ) ;
 c_sm -> set_open_read_tries ( 5 ) ;
 c_sm -> set_open_write_tries ( 8 ) ;
 TSHttpTxnInfoIntGet ( txnp , TS_TXN_INFO_CACHE_HIT_RWW , & ival_read ) ;
 if ( ival_read == 0 ) {
 SDK_RPRINT ( test , "TSHttpTxnInfoIntGet" , "TestCase1" , TC_FAIL , "Failed on %d, %d != %d" , TS_TXN_INFO_CACHE_HIT_RWW , ival_read , 1 ) ;
 success = false ;
 }
 TSHttpTxnInfoIntGet ( txnp , TS_TXN_INFO_CACHE_OPEN_READ_TRIES , & ival_read ) ;
 if ( ival_read != 5 ) {
 SDK_RPRINT ( test , "TSHttpTxnInfoIntGet" , "TestCase1" , TC_FAIL , "Failed on %d, %d != %d" , TS_TXN_INFO_CACHE_HIT_RWW , ival_read , 5 ) ;
 success = false ;
 }
 TSHttpTxnInfoIntGet ( txnp , TS_TXN_INFO_CACHE_OPEN_WRITE_TRIES , & ival_read ) ;
 if ( ival_read != 8 ) {
 SDK_RPRINT ( test , "TSHttpTxnInfoIntGet" , "TestCase1" , TC_FAIL , "Failed on %d, %d != %d" , TS_TXN_INFO_CACHE_HIT_RWW , ival_read , 8 ) ;
 success = false ;
 }
 s -> destroy ( ) ;
 if ( success ) {
 * pstatus = REGRESSION_TEST_PASSED ;
 SDK_RPRINT ( test , "TSHttpTxnInfoIntGet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 return ;
 }