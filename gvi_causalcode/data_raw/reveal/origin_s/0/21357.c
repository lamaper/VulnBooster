static void purple_chat_msg ( struct groupchat * gc , char * message , int flags ) {
 PurpleConversation * pc = gc -> data ;
 purple_conv_chat_send ( purple_conversation_get_chat_data ( pc ) , message ) ;
 }