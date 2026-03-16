void fe_ircnet_init ( void ) {
 command_bind ( "ircnet" , NULL , ( SIGNAL_FUNC ) cmd_network ) ;
 command_bind ( "network" , NULL , ( SIGNAL_FUNC ) cmd_network ) ;
 command_bind ( "network list" , NULL , ( SIGNAL_FUNC ) cmd_network_list ) ;
 command_bind ( "network add" , NULL , ( SIGNAL_FUNC ) cmd_network_add ) ;
 command_bind ( "network modify" , NULL , ( SIGNAL_FUNC ) cmd_network_modify ) ;
 command_bind ( "network remove" , NULL , ( SIGNAL_FUNC ) cmd_network_remove ) ;
 command_set_options ( "network add" , "-kicks -msgs -modes -whois -cmdspeed " "-cmdmax -nick -alternate_nick -user -realname -host -autosendcmd -querychans -usermode -sasl_mechanism -sasl_username -sasl_password" ) ;
 command_set_options ( "network modify" , "-kicks -msgs -modes -whois -cmdspeed " "-cmdmax -nick -alternate_nick -user -realname -host -autosendcmd -querychans -usermode -sasl_mechanism -sasl_username -sasl_password" ) ;
 }