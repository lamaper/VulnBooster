GList * completion_get_channels ( SERVER_REC * server , const char * word ) {
 GList * list ;
 GSList * tmp ;
 int len ;
 g_return_val_if_fail ( word != NULL , NULL ) ;
 len = strlen ( word ) ;
 list = NULL ;
 tmp = server == NULL ? NULL : server -> channels ;
 for ( ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 CHANNEL_REC * rec = tmp -> data ;
 if ( g_ascii_strncasecmp ( rec -> visible_name , word , len ) == 0 ) list = g_list_append ( list , g_strdup ( rec -> visible_name ) ) ;
 else if ( g_ascii_strncasecmp ( rec -> name , word , len ) == 0 ) list = g_list_append ( list , g_strdup ( rec -> name ) ) ;
 }
 for ( tmp = setupchannels ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 CHANNEL_SETUP_REC * rec = tmp -> data ;
 if ( g_ascii_strncasecmp ( rec -> name , word , len ) == 0 && glist_find_icase_string ( list , rec -> name ) == NULL ) list = g_list_append ( list , g_strdup ( rec -> name ) ) ;
 }
 return list ;
 }