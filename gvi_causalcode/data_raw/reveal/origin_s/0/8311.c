static void sig_nick_changed ( CHANNEL_REC * channel , NICK_REC * nick , const char * oldnick ) {
 MODULE_CHANNEL_REC * mchannel ;
 LAST_MSG_REC * rec ;
 mchannel = MODULE_DATA ( channel ) ;
 rec = last_msg_find ( mchannel -> lastmsgs , oldnick ) ;
 if ( rec != NULL ) {
 g_free ( rec -> nick ) ;
 rec -> nick = g_strdup ( nick -> nick ) ;
 }
 }