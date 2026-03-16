REGRESSION_TEST ( SDK_API_TSMgmtGet ) ( RegressionTest * test , int , int * pstatus ) {
 const char * CONFIG_PARAM_COUNTER_NAME = "proxy.process.ssl.total_tickets_renewed" ;
 int CONFIG_PARAM_COUNTER_VALUE = 0 ;
 const char * CONFIG_PARAM_FLOAT_NAME = "proxy.config.http.background_fill_completed_threshold" ;
 float CONFIG_PARAM_FLOAT_VALUE = 0.0 ;
 const char * CONFIG_PARAM_INT_NAME = "proxy.config.http.cache.http" ;
 int CONFIG_PARAM_INT_VALUE = 1 ;
 const char * CONFIG_PARAM_STRING_NAME = "proxy.config.product_name" ;
 const char * CONFIG_PARAM_STRING_VALUE = "Traffic Server" ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 int err = 0 ;
 TSMgmtCounter cvalue = 0 ;
 TSMgmtFloat fvalue = 0.0 ;
 TSMgmtInt ivalue = - 1 ;
 TSMgmtString svalue = nullptr ;
 if ( TS_SUCCESS != TSMgmtCounterGet ( CONFIG_PARAM_COUNTER_NAME , & cvalue ) ) {
 SDK_RPRINT ( test , "TSMgmtCounterGet" , "TestCase1.1" , TC_FAIL , "can not get value of param %s" , CONFIG_PARAM_COUNTER_NAME ) ;
 err = 1 ;
 }
 else if ( cvalue != CONFIG_PARAM_COUNTER_VALUE ) {
 SDK_RPRINT ( test , "TSMgmtCounterGet" , "TestCase1.1" , TC_FAIL , "got incorrect value of param %s, should have been %d, found %d" , CONFIG_PARAM_COUNTER_NAME , CONFIG_PARAM_COUNTER_VALUE , cvalue ) ;
 err = 1 ;
 }
 else {
 SDK_RPRINT ( test , "TSMgmtCounterGet" , "TestCase1.1" , TC_PASS , "ok" ) ;
 }
 if ( ( TS_SUCCESS != TSMgmtFloatGet ( CONFIG_PARAM_FLOAT_NAME , & fvalue ) ) || ( fvalue != CONFIG_PARAM_FLOAT_VALUE ) ) {
 SDK_RPRINT ( test , "TSMgmtFloatGet" , "TestCase2" , TC_FAIL , "can not get value of param %s" , CONFIG_PARAM_FLOAT_NAME ) ;
 err = 1 ;
 }
 else {
 SDK_RPRINT ( test , "TSMgmtFloatGet" , "TestCase1.2" , TC_PASS , "ok" ) ;
 }
 if ( ( TSMgmtIntGet ( CONFIG_PARAM_INT_NAME , & ivalue ) != TS_SUCCESS ) || ( ivalue != CONFIG_PARAM_INT_VALUE ) ) {
 SDK_RPRINT ( test , "TSMgmtIntGet" , "TestCase1.3" , TC_FAIL , "can not get value of param %s" , CONFIG_PARAM_INT_NAME ) ;
 err = 1 ;
 }
 else {
 SDK_RPRINT ( test , "TSMgmtIntGet" , "TestCase1.3" , TC_PASS , "ok" ) ;
 }
 if ( TS_SUCCESS != TSMgmtStringGet ( CONFIG_PARAM_STRING_NAME , & svalue ) ) {
 SDK_RPRINT ( test , "TSMgmtStringGet" , "TestCase1.4" , TC_FAIL , "can not get value of param %s" , CONFIG_PARAM_STRING_NAME ) ;
 err = 1 ;
 }
 else if ( strcmp ( svalue , CONFIG_PARAM_STRING_VALUE ) != 0 ) {
 SDK_RPRINT ( test , "TSMgmtStringGet" , "TestCase1.4" , TC_FAIL , R "(got incorrect value of param %s, should have been " % s ", found " % s ")" , CONFIG_PARAM_STRING_NAME , CONFIG_PARAM_STRING_VALUE , svalue ) ;
 err = 1 ;
 }
 else {
 SDK_RPRINT ( test , "TSMgmtStringGet" , "TestCase1.4" , TC_PASS , "ok" ) ;
 }
 if ( err ) {
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 * pstatus = REGRESSION_TEST_PASSED ;
 SDK_RPRINT ( test , "TSMgmtGet" , "TestCase1" , TC_PASS , "ok" ) ;
 return ;
 }