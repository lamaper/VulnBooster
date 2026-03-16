void fe_channels_deinit ( void ) {
 signal_remove ( "channel created" , ( SIGNAL_FUNC ) signal_channel_created ) ;
 signal_remove ( "channel destroyed" , ( SIGNAL_FUNC ) signal_channel_destroyed ) ;
 signal_remove ( "window item changed" , ( SIGNAL_FUNC ) signal_window_item_changed ) ;
 signal_remove ( "server disconnected" , ( SIGNAL_FUNC ) sig_disconnected ) ;
 signal_remove ( "channel joined" , ( SIGNAL_FUNC ) sig_channel_joined ) ;
 command_unbind ( "join" , ( SIGNAL_FUNC ) cmd_join ) ;
 command_unbind ( "channel" , ( SIGNAL_FUNC ) cmd_channel ) ;
 command_unbind ( "channel add" , ( SIGNAL_FUNC ) cmd_channel_add ) ;
 command_unbind ( "channel modify" , ( SIGNAL_FUNC ) cmd_channel_modify ) ;
 command_unbind ( "channel remove" , ( SIGNAL_FUNC ) cmd_channel_remove ) ;
 command_unbind ( "channel list" , ( SIGNAL_FUNC ) cmd_channel_list ) ;
 command_unbind ( "names" , ( SIGNAL_FUNC ) cmd_names ) ;
 command_unbind ( "cycle" , ( SIGNAL_FUNC ) cmd_cycle ) ;
 }