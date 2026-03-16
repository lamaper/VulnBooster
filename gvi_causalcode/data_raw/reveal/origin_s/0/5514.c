static void sig_nick_removed ( CHANNEL_REC * channel , NICK_REC * nick ) {
 MODULE_CHANNEL_REC * mchannel ;
 LAST_MSG_REC * rec ;
 mchannel = MODULE_DATA ( channel ) ;
 rec = last_msg_find ( mchannel -> lastmsgs , nick -> nick ) ;
 if ( rec != NULL ) last_msg_destroy ( & mchannel -> lastmsgs , rec ) ;
 }