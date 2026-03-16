int server_handler ( TSCont contp , TSEvent event , void * data ) {
 SDK_NetVConn_Params * params = ( SDK_NetVConn_Params * ) TSContDataGet ( contp ) ;
 if ( event == TS_EVENT_NET_ACCEPT ) {
 SDK_RPRINT ( params -> test , params -> api , "ServerEvent NET_ACCEPT" , TC_PASS , "ok" ) ;
 params -> buffer = TSIOBufferCreate ( ) ;
 params -> vc = ( TSVConn ) data ;
 TSVConnRead ( ( TSVConn ) data , contp , params -> buffer , 100 ) ;
 }
 else if ( event == TS_EVENT_VCONN_EOS ) {
 TSContDestroy ( contp ) ;
 SDK_RPRINT ( params -> test , params -> api , "ServerEvent EOS" , TC_PASS , "ok" ) ;
 * params -> pstatus = REGRESSION_TEST_PASSED ;
 delete params ;
 }
 else if ( event == TS_EVENT_VCONN_READ_READY ) {
 SDK_RPRINT ( params -> test , params -> api , "ServerEvent READ_READY" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( params -> test , params -> api , "ServerEvent" , TC_FAIL , "received unexpected event %d" , event ) ;
 * params -> pstatus = REGRESSION_TEST_FAILED ;
 delete params ;
 }
 return 1 ;
 }