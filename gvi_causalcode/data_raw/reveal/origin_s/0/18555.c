static void sig_server_disconnected ( SERVER_REC * server ) {
 g_return_if_fail ( server != NULL ) ;
 printformat ( server , NULL , MSGLEVEL_CLIENTNOTICE , TXT_CONNECTION_LOST , server -> connrec -> address ) ;
 }