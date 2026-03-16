REGRESSION_TEST ( SDK_API_TSNetVConn ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 SDK_NetVConn_Params * params = new SDK_NetVConn_Params ( "TSNetAccept" , test , pstatus ) ;
 params -> port = 12345 ;
 TSCont server_cont = TSContCreate ( server_handler , TSMutexCreate ( ) ) ;
 TSCont client_cont = TSContCreate ( client_handler , TSMutexCreate ( ) ) ;
 TSContDataSet ( server_cont , params ) ;
 TSContDataSet ( client_cont , params ) ;
 TSNetAccept ( server_cont , params -> port , - 1 , 0 ) ;
 IpEndpoint addr ;
 ats_ip4_set ( & addr , htonl ( INADDR_LOOPBACK ) , htons ( params -> port ) ) ;
 TSNetConnect ( client_cont , & addr . sa ) ;
 }