GList * completion_get_servertags ( const char * word ) {
 GList * list ;
 GSList * tmp ;
 int len ;
 g_return_val_if_fail ( word != NULL , NULL ) ;
 len = strlen ( word ) ;
 list = NULL ;
 for ( tmp = servers ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 SERVER_REC * rec = tmp -> data ;
 if ( g_ascii_strncasecmp ( rec -> tag , word , len ) == 0 ) {
 if ( rec == active_win -> active_server ) list = g_list_prepend ( list , g_strdup ( rec -> tag ) ) ;
 else list = g_list_append ( list , g_strdup ( rec -> tag ) ) ;
 }
 }
 return list ;
 }