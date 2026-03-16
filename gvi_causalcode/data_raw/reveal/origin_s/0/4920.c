void fe_server_init ( void ) {
 command_bind ( "server" , NULL , ( SIGNAL_FUNC ) cmd_server ) ;
 command_bind ( "server connect" , NULL , ( SIGNAL_FUNC ) cmd_server_connect ) ;
 command_bind ( "server add" , NULL , ( SIGNAL_FUNC ) cmd_server_add ) ;
 command_bind ( "server modify" , NULL , ( SIGNAL_FUNC ) cmd_server_modify ) ;
 command_bind ( "server remove" , NULL , ( SIGNAL_FUNC ) cmd_server_remove ) ;
 command_bind_first ( "server" , NULL , ( SIGNAL_FUNC ) server_command ) ;
 command_bind_first ( "disconnect" , NULL , ( SIGNAL_FUNC ) server_command ) ;
 command_set_options ( "server add" , "4 6 !! ssl nossl +ssl_cert +ssl_pkey +ssl_pass ssl_verify nossl_verify +ssl_cafile +ssl_capath +ssl_ciphers +ssl_fingerprint tls notls +tls_cert +tls_pkey +tls_pass tls_verify notls_verify +tls_cafile +tls_capath +tls_ciphers +tls_pinned_cert +tls_pinned_pubkey auto noauto proxy noproxy -host -port noautosendcmd" ) ;
 command_set_options ( "server modify" , "4 6 !! ssl nossl +ssl_cert +ssl_pkey +ssl_pass ssl_verify nossl_verify +ssl_cafile +ssl_capath +ssl_ciphers +ssl_fingerprint tls notls +tls_cert +tls_pkey +tls_pass tls_verify notls_verify +tls_cafile +tls_capath +tls_ciphers +tls_pinned_cert +tls_pinned_pubkey auto noauto proxy noproxy -host -port noautosendcmd" ) ;
 signal_add ( "server looking" , ( SIGNAL_FUNC ) sig_server_looking ) ;
 signal_add ( "server connecting" , ( SIGNAL_FUNC ) sig_server_connecting ) ;
 signal_add ( "server connected" , ( SIGNAL_FUNC ) sig_server_connected ) ;
 signal_add ( "server connect failed" , ( SIGNAL_FUNC ) sig_connect_failed ) ;
 signal_add ( "server disconnected" , ( SIGNAL_FUNC ) sig_server_disconnected ) ;
 signal_add ( "server quit" , ( SIGNAL_FUNC ) sig_server_quit ) ;
 signal_add ( "server lag disconnect" , ( SIGNAL_FUNC ) sig_server_lag_disconnected ) ;
 signal_add ( "server reconnect remove" , ( SIGNAL_FUNC ) sig_server_reconnect_removed ) ;
 signal_add ( "server reconnect not found" , ( SIGNAL_FUNC ) sig_server_reconnect_not_found ) ;
 signal_add ( "chat protocol unknown" , ( SIGNAL_FUNC ) sig_chat_protocol_unknown ) ;
 }