REGRESSION_TEST ( SDK_API_TSTextLog ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSTextLogObject log ;
 TSReturnCode retVal ;
 char logname [ PATH_NAME_MAX ] ;
 char fullpath_logname [ PATH_NAME_MAX ] ;
 ats_scoped_str tmp ( RecConfigReadLogDir ( ) ) ;
 snprintf ( logname , sizeof ( logname ) , "RegressionTestLog%d.log" , ( int ) getpid ( ) ) ;
 snprintf ( fullpath_logname , sizeof ( fullpath_logname ) , "%s/%s" , ( const char * ) tmp , logname ) ;
 unlink ( fullpath_logname ) ;
 retVal = TSTextLogObjectCreate ( logname , TS_LOG_MODE_ADD_TIMESTAMP , & log ) ;
 if ( retVal != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSTextLogObjectCreate" , "TestCase1" , TC_FAIL , "can not create log object" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSTextLogObjectCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 retVal = TSTextLogObjectWrite ( log , ( char * ) LOG_TEST_PATTERN ) ;
 if ( retVal != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSTextLogObjectWrite" , "TestCase1" , TC_FAIL , "can not write to log object" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 else {
 SDK_RPRINT ( test , "TSTextLogObjectWrite" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 TSTextLogObjectFlush ( log ) ;
 SDK_RPRINT ( test , "TSTextLogObjectFlush" , "TestCase1" , TC_PASS , "ok" ) ;
 TSCont log_test_cont = TSContCreate ( log_test_handler , TSMutexCreate ( ) ) ;
 LogTestData * data = ( LogTestData * ) TSmalloc ( sizeof ( LogTestData ) ) ;
 data -> test = test ;
 data -> pstatus = pstatus ;
 data -> fullpath_logname = TSstrdup ( fullpath_logname ) ;
 data -> magic = MAGIC_ALIVE ;
 data -> log = log ;
 TSContDataSet ( log_test_cont , data ) ;
 TSContSchedule ( log_test_cont , 6000 , TS_THREAD_POOL_DEFAULT ) ;
 return ;
 }