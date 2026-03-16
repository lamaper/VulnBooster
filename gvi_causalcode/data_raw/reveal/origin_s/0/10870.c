static void sig_server_connected ( SERVER_REC * server ) {
 g_return_if_fail ( server != NULL ) ;
 printformat ( server , NULL , MSGLEVEL_CLIENTNOTICE , TXT_CONNECTION_ESTABLISHED , server -> connrec -> address ) ;
 }