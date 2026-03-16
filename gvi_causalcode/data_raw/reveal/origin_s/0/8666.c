REGRESSION_TEST ( SDK_API_TSPortDescriptor ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSPortDescriptor port ;
 char desc [ 64 ] ;
 SDK_NetVConn_Params * params = new SDK_NetVConn_Params ( "TSPortDescriptorAccept" , test , pstatus ) ;
 TSCont server_cont = TSContCreate ( server_handler , TSMutexCreate ( ) ) ;
 TSCont client_cont = TSContCreate ( client_handler , TSMutexCreate ( ) ) ;
 params -> port = 54321 ;
 TSContDataSet ( server_cont , params ) ;
 TSContDataSet ( client_cont , params ) ;
 port = TSPortDescriptorParse ( nullptr ) ;
 if ( port ) {
 SDK_RPRINT ( test , "TSPortDescriptorParse" , "NULL port descriptor" , TC_FAIL , "TSPortDescriptorParse(NULL) returned %s" , port ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 snprintf ( desc , sizeof ( desc ) , "%u" , params -> port ) ;
 port = TSPortDescriptorParse ( desc ) ;
 if ( TSPortDescriptorAccept ( port , server_cont ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSPortDescriptorParse" , "Basic port descriptor" , TC_FAIL , "TSPortDescriptorParse(%s) returned TS_ERROR" , desc ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 IpEndpoint addr ;
 ats_ip4_set ( & addr , htonl ( INADDR_LOOPBACK ) , htons ( params -> port ) ) ;
 TSNetConnect ( client_cont , & addr . sa ) ;
 }