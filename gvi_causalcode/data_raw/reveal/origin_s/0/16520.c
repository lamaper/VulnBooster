static void sig_channel_joined ( CHANNEL_REC * channel ) {
 if ( settings_get_bool ( "show_names_on_join" ) && ! channel -> session_rejoin ) fe_channels_nicklist ( channel , CHANNEL_NICKLIST_FLAG_ALL ) ;
 }