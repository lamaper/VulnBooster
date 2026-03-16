void fe_channels_init ( void ) {
 settings_add_bool ( "lookandfeel" , "autoclose_windows" , TRUE ) ;
 settings_add_bool ( "lookandfeel" , "show_names_on_join" , TRUE ) ;
 settings_add_int ( "lookandfeel" , "names_max_columns" , 6 ) ;
 settings_add_int ( "lookandfeel" , "names_max_width" , 0 ) ;
 signal_add ( "channel created" , ( SIGNAL_FUNC ) signal_channel_created ) ;
 signal_add ( "channel destroyed" , ( SIGNAL_FUNC ) signal_channel_destroyed ) ;
 signal_add_last ( "window item changed" , ( SIGNAL_FUNC ) signal_window_item_changed ) ;
 signal_add_last ( "server disconnected" , ( SIGNAL_FUNC ) sig_disconnected ) ;
 signal_add_last ( "channel joined" , ( SIGNAL_FUNC ) sig_channel_joined ) ;
 command_bind ( "join" , NULL , ( SIGNAL_FUNC ) cmd_join ) ;
 command_bind ( "channel" , NULL , ( SIGNAL_FUNC ) cmd_channel ) ;
 command_bind ( "channel add" , NULL , ( SIGNAL_FUNC ) cmd_channel_add ) ;
 command_bind ( "channel modify" , NULL , ( SIGNAL_FUNC ) cmd_channel_modify ) ;
 command_bind ( "channel remove" , NULL , ( SIGNAL_FUNC ) cmd_channel_remove ) ;
 command_bind ( "channel list" , NULL , ( SIGNAL_FUNC ) cmd_channel_list ) ;
 command_bind ( "names" , NULL , ( SIGNAL_FUNC ) cmd_names ) ;
 command_bind ( "cycle" , NULL , ( SIGNAL_FUNC ) cmd_cycle ) ;
 command_set_options ( "channel add" , "auto noauto -bots -botcmd" ) ;
 command_set_options ( "channel modify" , "auto noauto -bots -botcmd" ) ;
 command_set_options ( "names" , "count ops halfops voices normal" ) ;
 command_set_options ( "join" , "invite window" ) ;
 }