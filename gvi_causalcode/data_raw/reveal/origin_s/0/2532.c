void purple_chat_leave ( struct groupchat * gc ) {
 PurpleConversation * pc = gc -> data ;
 purple_conversation_destroy ( pc ) ;
 }