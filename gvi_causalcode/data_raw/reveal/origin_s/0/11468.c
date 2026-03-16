void fe_server_deinit ( void ) {
 command_unbind ( "server" , ( SIGNAL_FUNC ) cmd_server ) ;
 command_unbind ( "server connect" , ( SIGNAL_FUNC ) cmd_server_connect ) ;
 command_unbind ( "server add" , ( SIGNAL_FUNC ) cmd_server_add ) ;
 command_unbind ( "server modify" , ( SIGNAL_FUNC ) cmd_server_modify ) ;
 command_unbind ( "server remove" , ( SIGNAL_FUNC ) cmd_server_remove ) ;
 command_unbind ( "server" , ( SIGNAL_FUNC ) server_command ) ;
 command_unbind ( "disconnect" , ( SIGNAL_FUNC ) server_command ) ;
 signal_remove ( "server looking" , ( SIGNAL_FUNC ) sig_server_looking ) ;
 signal_remove ( "server connecting" , ( SIGNAL_FUNC ) sig_server_connecting ) ;
 signal_remove ( "server connected" , ( SIGNAL_FUNC ) sig_server_connected ) ;
 signal_remove ( "server connect failed" , ( SIGNAL_FUNC ) sig_connect_failed ) ;
 signal_remove ( "server disconnected" , ( SIGNAL_FUNC ) sig_server_disconnected ) ;
 signal_remove ( "server quit" , ( SIGNAL_FUNC ) sig_server_quit ) ;
 signal_remove ( "server lag disconnect" , ( SIGNAL_FUNC ) sig_server_lag_disconnected ) ;
 signal_remove ( "server reconnect remove" , ( SIGNAL_FUNC ) sig_server_reconnect_removed ) ;
 signal_remove ( "server reconnect not found" , ( SIGNAL_FUNC ) sig_server_reconnect_not_found ) ;
 signal_remove ( "chat protocol unknown" , ( SIGNAL_FUNC ) sig_chat_protocol_unknown ) ;
 }