REGRESSION_TEST ( SDK_API_OVERRIDABLE_CONFIGS ) ( RegressionTest * test , int , int * pstatus ) {
 const char * conf ;
 TSOverridableConfigKey key ;
 TSRecordDataType type ;
 HttpSM * s = HttpSM : : allocate ( ) ;
 bool success = true ;
 TSHttpTxn txnp = reinterpret_cast < TSHttpTxn > ( s ) ;
 InkRand generator ( 17 ) ;
 TSMgmtInt ival_read , ival_rand ;
 TSMgmtFloat fval_read , fval_rand ;
 const char * sval_read ;
 const char * test_string = "The Apache Traffic Server" ;
 int len ;
 s -> init ( ) ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 for ( int i = TS_CONFIG_NULL + 1 ;
 i < TS_CONFIG_LAST_ENTRY ;
 ++ i ) {
 conf = SDK_Overridable_Configs [ i ] ;
 if ( TS_SUCCESS == TSHttpTxnConfigFind ( conf , - 1 , & key , & type ) ) {
 if ( key != i ) {
 SDK_RPRINT ( test , "TSHttpTxnConfigFind" , "TestCase1" , TC_FAIL , "Failed on %s, expected %d, got %d" , conf , i , key ) ;
 success = false ;
 continue ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpTxnConfigFind" , "TestCase1" , TC_FAIL , "Call returned unexpected TS_ERROR for %s" , conf ) ;
 success = false ;
 continue ;
 }
 switch ( type ) {
 case TS_RECORDDATATYPE_INT : ival_rand = generator . random ( ) % 126 ;
 TSHttpTxnConfigIntSet ( txnp , key , ival_rand ) ;
 TSHttpTxnConfigIntGet ( txnp , key , & ival_read ) ;
 if ( ival_rand != ival_read ) {
 SDK_RPRINT ( test , "TSHttpTxnConfigIntSet" , "TestCase1" , TC_FAIL , "Failed on %s, %d != %d" , conf , ival_read , ival_rand ) ;
 success = false ;
 continue ;
 }
 break ;
 case TS_RECORDDATATYPE_FLOAT : fval_rand = generator . random ( ) ;
 TSHttpTxnConfigFloatSet ( txnp , key , fval_rand ) ;
 TSHttpTxnConfigFloatGet ( txnp , key , & fval_read ) ;
 if ( fval_rand != fval_read ) {
 SDK_RPRINT ( test , "TSHttpTxnConfigFloatSet" , "TestCase1" , TC_FAIL , "Failed on %s, %f != %f" , conf , fval_read , fval_rand ) ;
 success = false ;
 continue ;
 }
 break ;
 case TS_RECORDDATATYPE_STRING : TSHttpTxnConfigStringSet ( txnp , key , test_string , - 1 ) ;
 TSHttpTxnConfigStringGet ( txnp , key , & sval_read , & len ) ;
 if ( test_string != sval_read ) {
 SDK_RPRINT ( test , "TSHttpTxnConfigStringSet" , "TestCase1" , TC_FAIL , "Failed on %s, %s != %s" , conf , sval_read , test_string ) ;
 success = false ;
 continue ;
 }
 break ;
 default : break ;
 }
 }
 s -> destroy ( ) ;
 if ( success ) {
 * pstatus = REGRESSION_TEST_PASSED ;
 SDK_RPRINT ( test , "TSHttpTxnConfigFind" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSHttpTxnConfigIntSet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSHttpTxnConfigFloatSet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSHttpTxnConfigStringSet" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 return ;
 }