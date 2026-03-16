static void sig_connect_failed ( SERVER_REC * server , gchar * msg ) {
 g_return_if_fail ( server != NULL ) ;
 if ( msg == NULL ) {
 printformat ( server , NULL , MSGLEVEL_CLIENTNOTICE , TXT_CONNECTION_LOST , server -> connrec -> address ) ;
 }
 else {
 printformat ( server , NULL , MSGLEVEL_CLIENTERROR , TXT_CANT_CONNECT , server -> connrec -> address , server -> connrec -> port , msg ) ;
 }
 }