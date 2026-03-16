int client_handler ( TSCont contp , TSEvent event , void * data ) {
 SDK_NetVConn_Params * params = ( SDK_NetVConn_Params * ) TSContDataGet ( contp ) ;
 if ( event == TS_EVENT_NET_CONNECT_FAILED ) {
 SDK_RPRINT ( params -> test , params -> api , "ClientConnect" , TC_FAIL , "can't connect to server" ) ;
 * params -> pstatus = REGRESSION_TEST_FAILED ;
 TSContDestroy ( contp ) ;
 return 1 ;
 }
 else if ( TS_EVENT_NET_CONNECT == event ) {
 sockaddr const * addr = TSNetVConnRemoteAddrGet ( static_cast < TSVConn > ( data ) ) ;
 uint16_t input_server_port = ats_ip_port_host_order ( addr ) ;
 UnixNetVConnection * vc = static_cast < UnixNetVConnection * > ( data ) ;
 ink_release_assert ( : : write ( vc -> con . fd , "Bob's your uncle" , 16 ) != 0 ) ;
 sleep ( 1 ) ;
 if ( ats_is_ip_loopback ( addr ) ) {
 SDK_RPRINT ( params -> test , params -> api , "TSNetVConnRemoteIPGet" , TC_PASS , "ok" ) ;
 }
 else {
 ip_text_buffer s , ipb ;
 IpEndpoint loopback ;
 ats_ip4_set ( & loopback , htonl ( INADDR_LOOPBACK ) ) ;
 SDK_RPRINT ( params -> test , params -> api , "TSNetVConnRemoteIPGet" , TC_FAIL , "server ip [%s] is incorrect - expected [%s]" , ats_ip_ntop ( addr , s , sizeof s ) , ats_ip_ntop ( & loopback . sa , ipb , sizeof ipb ) ) ;
 TSContDestroy ( contp ) ;
 * params -> pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 if ( input_server_port == params -> port ) {
 SDK_RPRINT ( params -> test , params -> api , "TSNetVConnRemotePortGet" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( params -> test , params -> api , "TSNetVConnRemotePortGet" , TC_FAIL , "server port [%d] is incorrect -- expected [%d]" , input_server_port , params -> port ) ;
 TSContDestroy ( contp ) ;
 * params -> pstatus = REGRESSION_TEST_FAILED ;
 return 1 ;
 }
 SDK_RPRINT ( params -> test , params -> api , "TSNetConnect" , TC_PASS , "ok" ) ;
 TSVConnClose ( ( TSVConn ) data ) ;
 }
 TSContDestroy ( contp ) ;
 return 1 ;
 }