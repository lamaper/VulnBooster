EXCLUSIVE_REGRESSION_TEST ( SDK_API_HttpParentProxySet_Success ) ( RegressionTest * test , int level , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 if ( level < REGRESSION_TEST_EXTENDED ) {
 * pstatus = REGRESSION_TEST_NOT_RUN ;
 return ;
 }
 TSCont cont = TSContCreate ( parent_proxy_handler , TSMutexCreate ( ) ) ;
 if ( cont == nullptr ) {
 SDK_RPRINT ( test , "TSHttpTxnParentProxySet" , "SuccessCase" , TC_FAIL , "Unable to create continuation" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 ParentTest * ptest = new ParentTest ( test , pstatus ) ;
 ptest -> testcase = "SuccessCase" ;
 ptest -> handler = parent_proxy_success ;
 TSContDataSet ( cont , ptest ) ;
 TSHttpHookAdd ( TS_HTTP_READ_REQUEST_HDR_HOOK , cont ) ;
 ptest -> os = synserver_create ( SYNSERVER_LISTEN_PORT , TSContCreate ( synserver_vc_accept , TSMutexCreate ( ) ) ) ;
 synserver_start ( ptest -> os ) ;
 TSContSchedule ( cont , 25 , TS_THREAD_POOL_DEFAULT ) ;
 }