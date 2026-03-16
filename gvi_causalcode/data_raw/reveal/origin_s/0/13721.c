static void sig_message_private ( SERVER_REC * server , const char * msg , const char * nick , const char * address ) {
 g_return_if_fail ( server != NULL ) ;
 g_return_if_fail ( nick != NULL ) ;
 SERVER_LAST_MSG_ADD ( server , nick ) ;
 }