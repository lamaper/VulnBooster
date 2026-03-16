static void cmd_channel_list_joined ( void ) {
 CHANNEL_REC * channel ;
 GString * nicks ;
 GSList * nicklist , * tmp , * ntmp ;
 if ( channels == NULL ) {
 printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_NOT_IN_CHANNELS ) ;
 return ;
 }
 channel = CHANNEL ( active_win -> active ) ;
 if ( channel != NULL ) printformat ( NULL , NULL , MSGLEVEL_CLIENTNOTICE , TXT_CURRENT_CHANNEL , channel -> visible_name ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTCRAP , TXT_CHANLIST_HEADER ) ;
 for ( tmp = channels ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 channel = tmp -> data ;
 nicklist = nicklist_getnicks ( channel ) ;
 nicks = g_string_new ( NULL ) ;
 for ( ntmp = nicklist ;
 ntmp != NULL ;
 ntmp = ntmp -> next ) {
 NICK_REC * rec = ntmp -> data ;
 g_string_append_printf ( nicks , "%s " , rec -> nick ) ;
 }
 if ( nicks -> len > 1 ) g_string_truncate ( nicks , nicks -> len - 1 ) ;
 printformat ( NULL , NULL , MSGLEVEL_CLIENTCRAP , TXT_CHANLIST_LINE , channel -> visible_name , channel -> mode , channel -> server -> tag , nicks -> str ) ;
 g_slist_free ( nicklist ) ;
 g_string_free ( nicks , TRUE ) ;
 }
 }