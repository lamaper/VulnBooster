void purple_chat_set_topic ( struct groupchat * gc , char * topic ) {
 PurpleConversation * pc = gc -> data ;
 PurpleConvChat * pcc = PURPLE_CONV_CHAT ( pc ) ;
 struct purple_data * pd = gc -> ic -> proto_data ;
 PurplePlugin * prpl = purple_plugins_find_with_id ( pd -> account -> protocol_id ) ;
 PurplePluginProtocolInfo * pi = prpl -> info -> extra_info ;
 if ( pi -> set_chat_topic ) {
 pi -> set_chat_topic ( purple_account_get_connection ( pd -> account ) , purple_conv_chat_get_id ( pcc ) , topic ) ;
 }
 }