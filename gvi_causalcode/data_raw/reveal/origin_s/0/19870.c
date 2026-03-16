void dcc_resume_init ( void ) {
 signal_add ( "ctcp msg dcc resume" , ( SIGNAL_FUNC ) ctcp_msg_dcc_resume ) ;
 signal_add ( "ctcp msg dcc accept" , ( SIGNAL_FUNC ) ctcp_msg_dcc_accept ) ;
 command_bind ( "dcc resume" , NULL , ( SIGNAL_FUNC ) cmd_dcc_resume ) ;
 }