static void print_reconnects ( void ) {
 GSList * tmp ;
 char * tag , * next_connect ;
 int left ;
 for ( tmp = reconnects ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 RECONNECT_REC * rec = tmp -> data ;
 SERVER_CONNECT_REC * conn = rec -> conn ;
 tag = g_strdup_printf ( "RECON-%d" , rec -> tag ) ;
 left = rec -> next_connect - time ( NULL ) ;
 next_connect = g_strdup_printf ( "%02d:%02d" , left / 60 , left % 60 ) ;
 printformat ( NULL , NULL , MSGLEVEL_CRAP , TXT_SERVER_RECONNECT_LIST , tag , conn -> address , conn -> port , conn -> chatnet == NULL ? "" : conn -> chatnet , conn -> nick , next_connect ) ;
 g_free ( next_connect ) ;
 g_free ( tag ) ;
 }
 }