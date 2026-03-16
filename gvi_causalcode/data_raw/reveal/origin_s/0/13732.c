static void sig_message_own_private ( SERVER_REC * server , const char * msg , const char * target , const char * origtarget ) {
 g_return_if_fail ( server != NULL ) ;
 if ( target != NULL && query_find ( server , target ) == NULL ) SERVER_LAST_MSG_ADD ( server , target ) ;
 }