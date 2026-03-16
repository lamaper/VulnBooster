static void sig_server_reconnect_removed ( RECONNECT_REC * reconnect ) {
 g_return_if_fail ( reconnect != NULL ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_RECONNECT_REMOVED , reconnect -> conn -> address , reconnect -> conn -> port , reconnect -> conn -> chatnet == NULL ? "" : reconnect -> conn -> chatnet ) ;
 }