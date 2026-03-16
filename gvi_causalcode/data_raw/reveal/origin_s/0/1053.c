static int cont_test_handler ( TSCont contp , TSEvent event , void * edata ) {
 TSHttpTxn txnp = ( TSHttpTxn ) edata ;
 ConnectTestData * data = nullptr ;
 int request_id = - 1 ;
 CHECK_SPURIOUS_EVENT ( contp , event , edata ) ;
 data = ( ConnectTestData * ) TSContDataGet ( contp ) ;
 TSReleaseAssert ( data -> magic == MAGIC_ALIVE ) ;
 TSReleaseAssert ( ( data -> test_case == TEST_CASE_CONNECT_ID1 ) || ( data -> test_case == TEST_CASE_CONNECT_ID2 ) ) ;
 TSDebug ( UTDBG_TAG , "Calling cont_test_handler with event %s (%d)" , TSHttpEventNameLookup ( event ) , event ) ;
 switch ( event ) {
 case TS_EVENT_HTTP_READ_REQUEST_HDR : TSDebug ( UTDBG_TAG , "cont_test_handler: event READ_REQUEST" ) ;
 request_id = get_request_id ( txnp ) ;
 TSReleaseAssert ( request_id != - 1 ) ;
 TSDebug ( UTDBG_TAG , "cont_test_handler: Request id = %d" , request_id ) ;
 if ( ( request_id != TEST_CASE_CONNECT_ID1 ) && ( request_id != TEST_CASE_CONNECT_ID2 ) ) {
 TSDebug ( UTDBG_TAG , "This is not an event for this test !" ) ;
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 goto done ;
 }
 if ( ( request_id == TEST_CASE_CONNECT_ID1 ) && ( data -> test_case == TEST_CASE_CONNECT_ID1 ) ) {
 TSDebug ( UTDBG_TAG , "Calling TSHttpTxnIntercept" ) ;
 TSHttpTxnIntercept ( data -> os -> accept_cont , txnp ) ;
 }
 else if ( ( request_id == TEST_CASE_CONNECT_ID2 ) && ( data -> test_case == TEST_CASE_CONNECT_ID2 ) ) {
 TSDebug ( UTDBG_TAG , "Calling TSHttpTxnServerIntercept" ) ;
 TSHttpTxnServerIntercept ( data -> os -> accept_cont , txnp ) ;
 }
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_TIMEOUT : if ( data -> browser -> status == REQUEST_INPROGRESS ) {
 TSDebug ( UTDBG_TAG , "Browser still waiting response..." ) ;
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 }
 else {
 char * body_response = get_body_ptr ( data -> browser -> response ) ;
 const char * body_expected ;
 if ( data -> test_case == TEST_CASE_CONNECT_ID1 ) {
 body_expected = "Body for response 9" ;
 }
 else {
 body_expected = "Body for response 10" ;
 }
 TSDebug ( UTDBG_TAG , "Body Response = \n|%s|\nBody Expected = \n|%s|" , body_response ? body_response : "*NULL*" , body_expected ) ;
 if ( ! body_response || strncmp ( body_response , body_expected , strlen ( body_expected ) ) != 0 ) {
 if ( data -> test_case == TEST_CASE_CONNECT_ID1 ) {
 SDK_RPRINT ( data -> test , "TSHttpConnect" , "TestCase1" , TC_FAIL , "Unexpected response" ) ;
 SDK_RPRINT ( data -> test , "TSHttpTxnIntercept" , "TestCase1" , TC_FAIL , "Unexpected response" ) ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpConnect" , "TestCase2" , TC_FAIL , "Unexpected response" ) ;
 SDK_RPRINT ( data -> test , "TSHttpTxnServerIntercept" , "TestCase2" , TC_FAIL , "Unexpected response" ) ;
 }
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 else {
 if ( data -> test_case == TEST_CASE_CONNECT_ID1 ) {
 SDK_RPRINT ( data -> test , "TSHttpConnect" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( data -> test , "TSHttpTxnIntercept" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpConnect" , "TestCase2" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( data -> test , "TSHttpTxnServerIntercept" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 * ( data -> pstatus ) = REGRESSION_TEST_PASSED ;
 }
 synclient_txn_delete ( data -> browser ) ;
 synserver_delete ( data -> os ) ;
 data -> os = nullptr ;
 data -> magic = MAGIC_DEAD ;
 TSfree ( data ) ;
 TSContDataSet ( contp , nullptr ) ;
 }
 break ;
 default : * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( data -> test , "TSHttpConnect" , "TestCase1 or 2" , TC_FAIL , "Unexpected event %d" , event ) ;
 break ;
 }
 done : return TS_EVENT_IMMEDIATE ;
 }