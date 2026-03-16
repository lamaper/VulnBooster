void dcc_resume_deinit ( void ) {
 signal_remove ( "ctcp msg dcc resume" , ( SIGNAL_FUNC ) ctcp_msg_dcc_resume ) ;
 signal_remove ( "ctcp msg dcc accept" , ( SIGNAL_FUNC ) ctcp_msg_dcc_accept ) ;
 command_unbind ( "dcc resume" , ( SIGNAL_FUNC ) cmd_dcc_resume ) ;
 }