void purple_chat_kick ( struct groupchat * gc , char * who , const char * message ) {
 PurpleConversation * pc = gc -> data ;
 char * str = g_strdup_printf ( "kick %s %s" , who , message ) ;
 purple_conversation_do_command ( pc , str , NULL , NULL ) ;
 g_free ( str ) ;
 }