static void sig_erase_complete_msg ( WINDOW_REC * window , const char * word , const char * line ) {
 SERVER_REC * server ;
 MODULE_SERVER_REC * mserver ;
 GSList * tmp ;
 server = line_get_server ( line ) ;
 if ( server == NULL ) {
 server = window -> active_server ;
 if ( server == NULL ) return ;
 }
 if ( * word == '\0' ) return ;
 completion_last_message_remove ( word ) ;
 if ( server != NULL ) {
 mserver = MODULE_DATA ( server ) ;
 for ( tmp = mserver -> lastmsgs ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 LAST_MSG_REC * rec = tmp -> data ;
 if ( g_ascii_strcasecmp ( rec -> nick , word ) == 0 ) {
 last_msg_destroy ( & mserver -> lastmsgs , rec ) ;
 break ;
 }
 }
 }
 }