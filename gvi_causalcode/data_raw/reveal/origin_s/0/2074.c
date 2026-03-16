static int ssn_handler ( TSCont contp , TSEvent event , void * edata ) {
 TSHttpTxn txnp = nullptr ;
 ContData * data = nullptr ;
 data = ( ContData * ) TSContDataGet ( contp ) ;
 if ( data == nullptr ) {
 switch ( event ) {
 case TS_EVENT_HTTP_SSN_START : TSHttpSsnReenable ( ( TSHttpSsn ) edata , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_IMMEDIATE : case TS_EVENT_TIMEOUT : break ;
 case TS_EVENT_HTTP_TXN_START : default : TSHttpTxnReenable ( ( TSHttpTxn ) edata , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 }
 return 0 ;
 }
 switch ( event ) {
 case TS_EVENT_HTTP_SSN_START : data -> ssnp = ( TSHttpSsn ) edata ;
 TSHttpSsnHookAdd ( data -> ssnp , TS_HTTP_TXN_START_HOOK , contp ) ;
 TSHttpSsnReenable ( data -> ssnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_HTTP_TXN_START : TSSkipRemappingSet ( ( TSHttpTxn ) edata , 1 ) ;
 SDK_RPRINT ( data -> test , "TSHttpSsnReenable" , "TestCase" , TC_PASS , "ok" ) ;
 data -> test_passed_ssn_reenable ++ ;
 {
 txnp = ( TSHttpTxn ) edata ;
 TSHttpSsn ssnp = TSHttpTxnSsnGet ( txnp ) ;
 if ( ssnp != data -> ssnp ) {
 SDK_RPRINT ( data -> test , "TSHttpSsnHookAdd" , "TestCase" , TC_FAIL , "Value's mismatch" ) ;
 data -> test_passed_ssn_hook_add -- ;
 SDK_RPRINT ( data -> test , "TSHttpTxnSsnGet" , "TestCase" , TC_FAIL , "Session doesn't match" ) ;
 data -> test_passed_txn_ssn_get -- ;
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpSsnHookAdd" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_ssn_hook_add ++ ;
 SDK_RPRINT ( data -> test , "TSHttpTxnSsnGet" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_ssn_get ++ ;
 }
 TSHttpTxnHookAdd ( txnp , TS_HTTP_OS_DNS_HOOK , contp ) ;
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 }
 break ;
 case TS_EVENT_HTTP_OS_DNS : SDK_RPRINT ( data -> test , "TSHttpTxnHookAdd" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_hook_add ++ ;
 txnp = ( TSHttpTxn ) edata ;
 TSHttpTxnHookAdd ( txnp , TS_HTTP_SEND_RESPONSE_HDR_HOOK , contp ) ;
 checkHttpTxnParentProxy ( data , txnp ) ;
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_ERROR ) ;
 break ;
 case TS_EVENT_HTTP_SEND_RESPONSE_HDR : SDK_RPRINT ( data -> test , "TSHttpTxnHookAdd" , "TestCase2" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_hook_add ++ ;
 txnp = ( TSHttpTxn ) edata ;
 if ( true ) {
 char * temp = TSstrdup ( ERROR_BODY ) ;
 TSHttpTxnErrorBodySet ( txnp , temp , strlen ( temp ) , nullptr ) ;
 }
 TSHttpTxnReenable ( txnp , TS_EVENT_HTTP_CONTINUE ) ;
 break ;
 case TS_EVENT_IMMEDIATE : case TS_EVENT_TIMEOUT : if ( data -> browser -> status == REQUEST_INPROGRESS ) {
 TSContSchedule ( contp , 25 , TS_THREAD_POOL_DEFAULT ) ;
 }
 else {
 char * temp = data -> browser -> response ;
 temp = strstr ( temp , "\r\n\r\n" ) ;
 if ( temp != nullptr ) {
 temp += strlen ( "\r\n\r\n" ) ;
 if ( ( temp [ 0 ] == '\0' ) || ( strncmp ( temp , "\r\n\r\n" , 4 ) == 0 ) ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnErrorBodySet" , "TestCase1" , TC_FAIL , "No Error Body found" ) ;
 data -> test_passed_txn_error_body_set -- ;
 }
 if ( strncmp ( temp , ERROR_BODY , strlen ( ERROR_BODY ) ) == 0 ) {
 SDK_RPRINT ( data -> test , "TSHttpTxnErrorBodySet" , "TestCase1" , TC_PASS , "ok" ) ;
 data -> test_passed_txn_error_body_set ++ ;
 }
 }
 else {
 SDK_RPRINT ( data -> test , "TSHttpTxnErrorBodySet" , "TestCase1" , TC_FAIL , "strstr returns NULL. Didn't find end of headers." ) ;
 data -> test_passed_txn_error_body_set -- ;
 }
 if ( ( data -> browser -> status == REQUEST_SUCCESS ) && ( data -> test_passed_ssn_hook_add == 1 ) && ( data -> test_passed_ssn_reenable == 1 ) && ( data -> test_passed_txn_ssn_get == 1 ) && ( data -> test_passed_txn_hook_add == 2 ) && ( data -> test_passed_txn_error_body_set == 1 ) && ( data -> test_passed_Parent_Proxy == true ) ) {
 * ( data -> pstatus ) = REGRESSION_TEST_PASSED ;
 }
 else {
 * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 }
 synclient_txn_delete ( data -> browser ) ;
 data -> os = nullptr ;
 data -> magic = MAGIC_DEAD ;
 TSfree ( data ) ;
 TSContDataSet ( contp , nullptr ) ;
 }
 break ;
 default : * ( data -> pstatus ) = REGRESSION_TEST_FAILED ;
 SDK_RPRINT ( data -> test , "TSHttpSsn" , "TestCase1" , TC_FAIL , "Unexpected event %d" , event ) ;
 break ;
 }
 return 0 ;
 }