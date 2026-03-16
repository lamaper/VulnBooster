static void sig_server_quit ( SERVER_REC * server , const char * msg ) {
 g_return_if_fail ( server != NULL ) ;
 printformat ( server , NULL , MSGLEVEL_CLIENTNOTICE , TXT_SERVER_QUIT , server -> connrec -> address , msg ) ;
 }