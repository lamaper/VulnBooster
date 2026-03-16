static int transform_hook_handler ( TSCont contp , TSEvent event , void * edata ) {
 TSHttpTxn txnp = nullptr ;
 TransformTestData * data = nullptr ;
 CHECK_SPURIOUS_EVENT ( contp , event , edata ) ;
 data = ( TransformTestData * ) TSContDataGet ( contp ) ;
 switch ( event ) {
 case TS_EVENT_HTTP_READ_REQUEST_HDR : txnp = ( TSHttpTxn ) edata ;
 TSSkipRemappingSet ( txnp , 1 ) ;
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_HTTP_READ_RESPONSE_HDR : txnp = ( TSHttpTxn ) edata ;
 if ( transformable ( txnp , data ) ) {
 transform_add ( txnp , data ) ;
 }
 {
 TSMBuffer bufp ;
 TSMLoc hdr ;
 TSMLoc field ;
 if ( TSHttpTxnClientReqGet ( txnp , & bufp , & hdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransform" , "TestCase" , TC_FAIL , "TSHttpTxnClientReqGet returns 0" ) ;
 }
 else {
 if ( TS_NULL_MLOC == ( field = TSMimeHdrFieldFind ( bufp , hdr , "Request" , - 1 ) ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransform" , "TestCase" , TC_FAIL , "Didn't find field request" ) ;
 }
 else {
 int reqid = TSMimeHdrFieldValueIntGet ( bufp , hdr , field , 0 ) ;
 if ( reqid == 1 ) {
 TSHttpTxnTransformedRespCache ( txnp , 0 ) ;
 TSHttpTxnUntransformedRespCache ( txnp , 1 ) ;
 }
 if ( reqid == 2 ) {
 TSHttpTxnTransformedRespCache ( txnp , 1 ) ;
 TSHttpTxnUntransformedRespCache ( txnp , 0 ) ;
 }
 if ( TSHandleMLocRelease ( bufp , hdr , field ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransform" , "TestCase" , TC_FAIL , "Unable to release handle to field in Client request" ) ;
 }
 }
 if ( TSHandleMLocRelease ( bufp , TS_NULL_MLOC , hdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransform" , "TestCase" , TC_FAIL , "Unable to release handle to Client request" ) ;
 }
 }
 }
 TSHttpTxnHookAdd ( txnp , TS_HTTP_SEND_RESPONSE_HDR_HOOK , contp ) ;
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_HTTP_SEND_RESPONSE_HDR : {
 TSMBuffer bufp ;
 TSMLoc hdr ;
 txnp = ( TSHttpTxn ) edata ;
 if ( TSHttpTxnTransformRespGet ( txnp , & bufp , & hdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransformRespGet" , "TestCase" , TC_FAIL , "TSHttpTxnTransformRespGet returns 0" ) ;
 data -> test_passed_txn_transform_resp_get = false ;
 }
 else {
 if ( ( bufp == reinterpret_cast < TSMBuffer > ( & ( ( ( HttpSM * ) txnp ) -> t_state . hdr_info . transform_response ) ) ) && ( hdr == reinterpret_cast < TSMLoc > ( ( & ( ( ( HttpSM * ) txnp ) -> t_state . hdr_info . transform_response ) ) -> m_http ) ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransformRespGet" , "TestCase" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransformRespGet" , "TestCase" , TC_FAIL , "Value's Mismatch" ) ;
 data -> test_passed_txn_transform_resp_get = false ;
 }
 if ( TSHandleMLocRelease ( bufp , TS_NULL_MLOC , hdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransformRespGet" , "TestCase" , TC_FAIL , "Unable to release handle to Transform header handle" ) ;
 }
 }
 }
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_IMMEDIATE : case TS_EVENT_TIMEOUT : switch ( data -> req_no ) {
 case 1 : if ( data -> browser1 -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 data -> req_no ++ ;
 Debug ( UTDBG_TAG "_transform" , "Running Browser 2" ) ;
 synclient_txn_send_request ( data -> browser2 , data -> request2 ) ;
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 case 2 : if ( data -> browser2 -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 data -> req_no ++ ;
 Debug ( UTDBG_TAG "_transform" , "Running Browser 3" ) ;
 synclient_txn_send_request ( data -> browser3 , data -> request1 ) ;
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 case 3 : if ( data -> browser3 -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 data -> req_no ++ ;
 Debug ( UTDBG_TAG "_transform" , "Running Browser 4" ) ;
 synclient_txn_send_request ( data -> browser4 , data -> request2 ) ;
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 case 4 : if ( data -> browser4 -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 synserver_delete ( data -> os ) ;
 data -> os = nullptr ;
 data -> req_no ++ ;
 TSfree ( data -> request1 ) ;
 TSfree ( data -> request2 ) ;
 break ;
 default : SDK_RPRINT ( data -> test , "TSHttpTxnTransform" , "TestCase" , TC_FAIL , "Something terribly wrong with the test" ) ;
 exit ( 0 ) ;
 }
 {
 if ( ( strstr ( data -> browser1 -> response , TRANSFORM_APPEND_STRING ) != nullptr ) && ( strstr ( data -> browser3 -> response , TRANSFORM_APPEND_STRING ) == nullptr ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnUntransformedResponseCache" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_untransformed_resp_cache = true ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnUntransformedResponseCache" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 if ( ( strstr ( data -> browser2 -> response , TRANSFORM_APPEND_STRING ) != nullptr ) && ( strstr ( data -> browser4 -> response , TRANSFORM_APPEND_STRING ) != nullptr ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransformedResponseCache" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_transformed_resp_cache = true ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnTransformedResponseCache" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 * ( data -> pstatus ) = REGRESSION_TEST_PASSED ;
 if ( data -> browser1 -> status != REQUEST_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSTransformCreate" , "TestCase1" , TC_FAIL , "Browser 1 status was not REQUEST_SUCCESS" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 if ( data -> browser2 -> status != REQUEST_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSTransformCreate" , "TestCase1" , TC_FAIL , "Browser 2 status was not REQUEST_SUCCESS" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 if ( data -> browser3 -> status != REQUEST_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSTransformCreate" , "TestCase1" , TC_FAIL , "Browser 3 status was not REQUEST_SUCCESS" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 if ( data -> browser4 -> status != REQUEST_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSTransformCreate" , "TestCase1" , TC_FAIL , "Browser 4 status was not REQUEST_SUCCESS" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 if ( data -> test_passed_txn_transform_resp_get != true ) {
 SDK_RPRINT ( data -> test , "TSTransformCreate" , "TestCase1" , TC_FAIL , "did not pass transform_resp_get" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 if ( data -> test_passed_txn_transformed_resp_cache != true ) {
 SDK_RPRINT ( data -> test , "TSTransformCreate" , "TestCase1" , TC_FAIL , "did not pass transformed_resp_cache" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 if ( data -> test_passed_txn_untransformed_resp_cache != true ) {
 SDK_RPRINT ( data -> test , "TSTransformCreate" , "TestCase1" , TC_FAIL , "did not pass untransformed_resp_cache" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 if ( data -> test_passed_transform_create != true ) {
 SDK_RPRINT ( data -> test , "TSTransformCreate" , "TestCase1" , TC_FAIL , "did not pass transform_create" ) ;
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 synclient_txn_delete ( data -> browser1 ) ;
 synclient_txn_delete ( data -> browser2 ) ;
 synclient_txn_delete ( data -> browser3 ) ;
 synclient_txn_delete ( data -> browser4 ) ;
 TSContDataSet ( contp , nullptr ) ;
 data -> magic = MAGIC_DEAD ;
 TSfree ( data ) ;
 }
 break ;
 default : * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( data -> test , "TSHttpTxnTransform" , "TestCase1" , TC_FAIL , "Unexpected event %d" , event ) ;
 break ;
 }
 return 0 ;
 }