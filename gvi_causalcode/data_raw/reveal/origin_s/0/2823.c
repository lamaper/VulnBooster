static void sig_channel_destroyed ( CHANNEL_REC * channel ) {
 MODULE_CHANNEL_REC * mchannel ;
 g_return_if_fail ( channel != NULL ) ;
 mchannel = MODULE_DATA ( channel ) ;
 while ( mchannel -> lastmsgs != NULL ) {
 last_msg_destroy ( & mchannel -> lastmsgs , mchannel -> lastmsgs -> data ) ;
 }
 }