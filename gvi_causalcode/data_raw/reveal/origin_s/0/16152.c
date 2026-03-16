static void sig_server_lag_disconnected ( SERVER_REC * server ) {
 g_return_if_fail ( server != NULL ) ;
 printformat ( server , NULL , MSGLEVEL_CLIENTNOTICE , TXT_LAG_DISCONNECTED , server -> connrec -> address , time ( NULL ) - server -> lag_sent . tv_sec ) ;
 }