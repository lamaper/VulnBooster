static void completion_msg_server ( GSList * * list , SERVER_REC * server , const char * nick , const char * prefix ) {
 LAST_MSG_REC * msg ;
 GSList * tmp ;
 int len ;
 g_return_if_fail ( nick != NULL ) ;
 len = strlen ( nick ) ;
 tmp = server == NULL ? global_lastmsgs : ( ( MODULE_SERVER_REC * ) MODULE_DATA ( server ) ) -> lastmsgs ;
 for ( ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 LAST_MSG_REC * rec = tmp -> data ;
 if ( len != 0 && g_ascii_strncasecmp ( rec -> nick , nick , len ) != 0 ) continue ;
 msg = g_new ( LAST_MSG_REC , 1 ) ;
 msg -> time = rec -> time ;
 msg -> nick = prefix == NULL || * prefix == '\0' ? g_strdup ( rec -> nick ) : g_strconcat ( prefix , " " , rec -> nick , NULL ) ;
 * list = g_slist_insert_sorted ( * list , msg , ( GCompareFunc ) last_msg_cmp ) ;
 }
 }