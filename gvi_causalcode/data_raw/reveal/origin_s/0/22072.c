static int cache_hook_handler ( TSCont contp , TSEvent event , void * edata ) {
 TSHttpTxn txnp = nullptr ;
 CacheTestData * data = nullptr ;
 CHECK_SPURIOUS_EVENT ( contp , event , edata ) ;
 data = ( CacheTestData * ) TSContDataGet ( contp ) ;
 switch ( event ) {
 case TS_EVENT_HTTP_READ_REQUEST_HDR : txnp = ( TSHttpTxn ) edata ;
 TSSkipRemappingSet ( txnp , 1 ) ;
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_HTTP_CACHE_LOOKUP_COMPLETE : {
 int lookup_status ;
 if ( data -> first_time == true ) {
 txnp = ( TSHttpTxn ) edata ;
 if ( TSHttpTxnCacheLookupStatusGet ( txnp , & lookup_status ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCacheLookupStatusGet" , "TestCase1" , TC_FAIL , "TSHttpTxnCacheLookupStatus doesn't return TS_SUCCESS" ) ;
 }
 else {
 if ( lookup_status == TS_CACHE_LOOKUP_MISS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCacheLookupStatusGet" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_cache_lookup_status = true ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnCacheLookupStatusGet" , "TestCase1" , TC_FAIL , "Incorrect Value returned by TSHttpTxnCacheLookupStatusGet" ) ;
 }
 }
 }
 else {
 txnp = ( TSHttpTxn ) edata ;
 if ( TSHttpTxnCacheLookupStatusGet ( txnp , & lookup_status ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCacheLookupStatusGet" , "TestCase2" , TC_FAIL , "TSHttpTxnCacheLookupStatus doesn't return TS_SUCCESS" ) ;
 data -> test_passed_txn_cache_lookup_status = false ;
 }
 else {
 if ( lookup_status == TS_CACHE_LOOKUP_HIT_FRESH ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCacheLookupStatusGet" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnCacheLookupStatusGet" , "TestCase2" , TC_FAIL , "Incorrect Value returned by TSHttpTxnCacheLookupStatusGet" ) ;
 data -> test_passed_txn_cache_lookup_status = false ;
 }
 }
 }
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 }
 break ;
 case TS_EVENT_HTTP_READ_CACHE_HDR : {
 TSMBuffer reqbuf ;
 TSMBuffer respbuf ;
 TSMLoc reqhdr ;
 TSMLoc resphdr ;
 txnp = ( TSHttpTxn ) edata ;
 if ( TSHttpTxnCachedReqGet ( txnp , & reqbuf , & reqhdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCachedReqGet" , "TestCase1" , TC_FAIL , "TSHttpTxnCachedReqGet returns 0" ) ;
 }
 else {
 if ( ( reqbuf == reinterpret_cast < TSMBuffer > ( ( ( HttpSM * ) txnp ) -> t_state . cache_req_hdr_heap_handle ) ) && ( reqhdr == reinterpret_cast < TSMLoc > ( ( ( ( HttpSM * ) txnp ) -> t_state . cache_info . object_read -> request_get ( ) ) -> m_http ) ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCachedReqGet" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_cached_req_get = true ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnCachedReqGet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 }
 if ( TSHttpTxnCachedRespGet ( txnp , & respbuf , & resphdr ) != TS_SUCCESS ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCachedRespGet" , "TestCase1" , TC_FAIL , "TSHttpTxnCachedRespGet returns 0" ) ;
 }
 else {
 if ( ( respbuf == reinterpret_cast < TSMBuffer > ( ( ( HttpSM * ) txnp ) -> t_state . cache_resp_hdr_heap_handle ) ) && ( resphdr == reinterpret_cast < TSMLoc > ( ( ( ( HttpSM * ) txnp ) -> t_state . cache_info . object_read -> response_get ( ) ) -> m_http ) ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCachedRespGet" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_cached_resp_get = true ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnCachedRespGet" , "TestCase1" , TC_FAIL , "Value's Mismatch" ) ;
 }
 }
 if ( ( TSHandleMLocRelease ( reqbuf , TS_NULL_MLOC , reqhdr ) != TS_SUCCESS ) || ( TSHandleMLocRelease ( respbuf , TS_NULL_MLOC , resphdr ) != TS_SUCCESS ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnCache" , "" , TC_FAIL , "Unable to release handle to headers." ) ;
 }
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 }
 break ;
 case TS_EVENT_IMMEDIATE : case TS_EVENT_TIMEOUT : if ( data -> first_time == true ) {
 if ( data -> browser1 -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 }
 else {
 if ( data -> browser2 -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 }
 {
 if ( data -> first_time == true ) {
 data -> first_time = false ;
 synserver_delete ( data -> os ) ;
 data -> os = nullptr ;
 synclient_txn_send_request ( data -> browser2 , data -> request ) ;
 ink_assert ( REQUEST_INPROGRESS == data -> browser2 -> status ) ;
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 return 0 ;
 }
 if ( ( data -> browser1 -> status == REQUEST_SUCCESS ) && ( data -> browser2 -> status == REQUEST_SUCCESS ) && ( data -> test_passed_txn_cached_req_get == true ) && ( data -> test_passed_txn_cached_resp_get == true ) && ( data -> test_passed_txn_cache_lookup_status == true ) ) {
 * ( data -> pstatus ) = REGRESSION_TEST_PASSED ;
 }
 else {
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 synclient_txn_delete ( data -> browser1 ) ;
 synclient_txn_delete ( data -> browser2 ) ;
 data -> magic = MAGIC_DEAD ;
 TSfree ( data -> request ) ;
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