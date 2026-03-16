void purple_chat_invite ( struct groupchat * gc , char * who , char * message ) {
 PurpleConversation * pc = gc -> data ;
 PurpleConvChat * pcc = PURPLE_CONV_CHAT ( pc ) ;
 struct purple_data * pd = gc -> ic -> proto_data ;
 serv_chat_invite ( purple_account_get_connection ( pd -> account ) , purple_conv_chat_get_id ( pcc ) , message && * message ? message : "Please join my chat" , who ) ;
 }