static void sig_chat_protocol_unknown ( const char * protocol ) {
 g_return_if_fail ( protocol != NULL ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTERROR , TXT_UNKNOWN_CHAT_PROTOCOL , protocol ) ;
 }