GList * completion_get_chatnets ( const char * word ) {
 GList * list ;
 GSList * tmp ;
 int len ;
 g_return_val_if_fail ( word != NULL , NULL ) ;
 len = strlen ( word ) ;
 list = NULL ;
 for ( tmp = chatnets ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 CHATNET_REC * rec = tmp -> data ;
 if ( g_ascii_strncasecmp ( rec -> name , word , len ) == 0 ) list = g_list_append ( list , g_strdup ( rec -> name ) ) ;
 }
 return list ;
 }