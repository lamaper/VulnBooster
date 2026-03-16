void fe_ircnet_deinit ( void ) {
 command_unbind ( "ircnet" , ( SIGNAL_FUNC ) cmd_network ) ;
 command_unbind ( "network" , ( SIGNAL_FUNC ) cmd_network ) ;
 command_unbind ( "network list" , ( SIGNAL_FUNC ) cmd_network_list ) ;
 command_unbind ( "network add" , ( SIGNAL_FUNC ) cmd_network_add ) ;
 command_unbind ( "network modify" , ( SIGNAL_FUNC ) cmd_network_modify ) ;
 command_unbind ( "network remove" , ( SIGNAL_FUNC ) cmd_network_remove ) ;
 }