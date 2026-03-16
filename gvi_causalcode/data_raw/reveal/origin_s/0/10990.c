static void sig_server_reconnect_not_found ( const char * tag ) {
 g_return_if_fail ( tag != NULL ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_RECONNECT_NOT_FOUND , tag ) ;
 }