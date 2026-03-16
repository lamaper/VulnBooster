static int altinfo_hook_handler ( TSCont contp , TSEvent event , void * edata ) {
 AltInfoTestData * data = nullptr ;
 TSHttpTxn txnp = nullptr ;
 CHECK_SPURIOUS_EVENT ( contp , event , edata ) ;
 data = ( AltInfoTestData * ) TSContDataGet ( contp ) ;
 switch ( event ) {
 case TS_EVENT_HTTP_READ_REQUEST_HDR : txnp = ( TSHttpTxn ) edata ;
 TSSkipRemappingSet ( txnp , 1 ) ;
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_HTTP_SELECT_ALT : {
 TSMBuffer clientreqbuf ;
 TSMBuffer cachereqbuf ;
 TSMBuffer cacherespbuf ;
 TSMLoc clientreqhdr ;
 TSMLoc cachereqhdr ;
 TSMLoc cacheresphdr ;
 TSHttpAltInfo infop = ( TSHttpAltInfo ) edata ;
 data -> run_at_least_once = true ;
 if ( TSHttpAltInfoClientReqGet ( infop , & clientreqbuf , & clientreqhdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoClientReqGet" , "TestCase" , TC_FAIL , "TSHttpAltInfoClientReqGet doesn't return TS_SUCCESS" ) ;
 data -> test_passed_txn_alt_info_client_req_get = false ;
 }
 else {
 if ( ( clientreqbuf == reinterpret_cast < TSMBuffer > ( & ( ( ( HttpAltInfo * ) infop ) -> m_client_req ) ) ) && ( clientreqhdr == reinterpret_cast < TSMLoc > ( ( ( HttpAltInfo * ) infop ) -> m_client_req . m_http ) ) ) {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoClientReqGet" , "TestCase" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoClientReqGet" , "TestCase" , TC_FAIL , "Value's Mismatch" ) ;
 data -> test_passed_txn_alt_info_client_req_get = false ;
 }
 }
 if ( TSHttpAltInfoCachedReqGet ( infop , & cachereqbuf , & cachereqhdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoCachedReqGet" , "TestCase" , TC_FAIL , "TSHttpAltInfoCachedReqGet doesn't return TS_SUCCESS" ) ;
 data -> test_passed_txn_alt_info_cached_req_get = false ;
 }
 else {
 if ( ( cachereqbuf == reinterpret_cast < TSMBuffer > ( & ( ( ( HttpAltInfo * ) infop ) -> m_cached_req ) ) ) && ( cachereqhdr == reinterpret_cast < TSMLoc > ( ( ( HttpAltInfo * ) infop ) -> m_cached_req . m_http ) ) ) {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoCachedReqGet" , "TestCase" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoCachedReqGet" , "TestCase" , TC_FAIL , "Value's Mismatch" ) ;
 data -> test_passed_txn_alt_info_cached_req_get = false ;
 }
 }
 if ( TSHttpAltInfoCachedRespGet ( infop , & cacherespbuf , & cacheresphdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoCachedRespGet" , "TestCase" , TC_FAIL , "TSHttpAltInfoCachedRespGet doesn't return TS_SUCCESS" ) ;
 data -> test_passed_txn_alt_info_cached_resp_get = false ;
 }
 else {
 if ( ( cacherespbuf == reinterpret_cast < TSMBuffer > ( & ( ( ( HttpAltInfo * ) infop ) -> m_cached_resp ) ) ) && ( cacheresphdr == reinterpret_cast < TSMLoc > ( ( ( HttpAltInfo * ) infop ) -> m_cached_resp . m_http ) ) ) {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoCachedRespGet" , "TestCase" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpAltInfoCachedRespGet" , "TestCase" , TC_FAIL , "Value's Mismatch" ) ;
 data -> test_passed_txn_alt_info_cached_resp_get = false ;
 }
 }
 TSHttpAltInfoQualitySet ( infop , 0.5 ) ;
 SDK_RPRINT ( data -> test , "TSHttpAltInfoQualitySet" , "TestCase" , TC_PASS , "ok" ) ;
 }
 break ;
 case TS_EVENT_IMMEDIATE : case TS_EVENT_TIMEOUT : if ( data -> first_time == true ) {
 if ( ( data -> browser1 -> status == REQUEST_INPROGRESS ) || ( data -> browser2 -> status == REQUEST_INPROGRESS ) ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 }
 else {
 if ( data -> browser3 -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 }
 {
 if ( data -> first_time == true ) {
 data -> first_time = false ;
 synserver_delete ( data -> os ) ;
 data -> os = nullptr ;
 synclient_txn_send_request ( data -> browser3 , data -> request3 ) ;
 TSHttpHookAdd ( TS_HTTP_SELECT_ALT_HOOK , contp ) ;
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 if ( ( data -> browser3 -> status == REQUEST_SUCCESS ) && ( data -> test_passed_txn_alt_info_client_req_get == true ) && ( data -> test_passed_txn_alt_info_cached_req_get == true ) && ( data -> test_passed_txn_alt_info_cached_resp_get == true ) && ( data -> test_passed_txn_alt_info_quality_set == true ) && ( data -> run_at_least_once == true ) ) {
 * ( data -> pstatus ) = REGRESSION_TEST_PASSED ;
 }
 else {
 if ( data -> run_at_least_once == false ) {
 SDK_RPRINT ( data -> test , "TSHttpAltInfo" , "All" , TC_FAIL , "Test not executed even once" ) ;
 }
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 synclient_txn_delete ( data -> browser1 ) ;
 synclient_txn_delete ( data -> browser2 ) ;
 synclient_txn_delete ( data -> browser3 ) ;
 TSfree ( data -> request1 ) ;
 TSfree ( data -> request2 ) ;
 TSfree ( data -> request3 ) ;
 data -> magic = MAGIC_DEAD ;
 TSfree ( data ) ;
 TSContDataSet ( contp , nullptr ) ;
 }
 break ;
 default : * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( data -> test , "TSHttpTxnCache" , "TestCase1" , TC_FAIL , "Unexpected event %d" , event ) ;
 break ;
 }
 return 0 ;
 }