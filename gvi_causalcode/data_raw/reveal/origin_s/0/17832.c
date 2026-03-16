GList * completion_get_servers ( const char * word ) {
 GList * list ;
 GSList * tmp ;
 int len ;
 g_return_val_if_fail ( word != NULL , NULL ) ;
 len = strlen ( word ) ;
 list = NULL ;
 for ( tmp = setupservers ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 SERVER_SETUP_REC * rec = tmp -> data ;
 if ( g_ascii_strncasecmp ( rec -> address , word , len ) == 0 ) list = g_list_append ( list , g_strdup ( rec -> address ) ) ;
 }
 return list ;
 }