EXCLUSIVE_REGRESSION_TEST ( SDK_API_TSHttpConnectServerIntercept ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSDebug ( UTDBG_TAG , "Starting test TSHttpConnectServerintercept" ) ;
 TSCont cont_test = TSContCreate ( cont_test_handler , TSMutexCreate ( ) ) ;
 ConnectTestData * data = ( ConnectTestData * ) TSmalloc ( sizeof ( ConnectTestData ) ) ;
 TSContDataSet ( cont_test , data ) ;
 data -> test = test ;
 data -> pstatus = pstatus ;
 data -> magic = MAGIC_ALIVE ;
 data -> test_case = TEST_CASE_CONNECT_ID2 ;
 TSHttpHookAdd ( TS_HTTP_READ_REQUEST_HDR_HOOK , cont_test ) ;
 data -> os = synserver_create ( SYNSERVER_DUMMY_PORT ) ;
 data -> browser = synclient_txn_create ( ) ;
 data -> request = generate_request ( 10 ) ;
 sockaddr_in addr ;
 ats_ip4_set ( & addr , 2 , 2 ) ;
 data -> vc = TSHttpConnect ( ats_ip_sa_cast ( & addr ) ) ;
 synclient_txn_send_request_to_vc ( data -> browser , data -> request , data -> vc ) ;
 TSContSchedule ( cont_test , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return ;
 }