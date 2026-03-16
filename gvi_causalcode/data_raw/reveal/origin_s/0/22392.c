GList * completion_get_aliases ( const char * word ) {
 CONFIG_NODE * node ;
 GList * list ;
 GSList * tmp ;
 int len ;
 g_return_val_if_fail ( word != NULL , NULL ) ;
 len = strlen ( word ) ;
 list = NULL ;
 node = iconfig_node_traverse ( "aliases" , FALSE ) ;
 tmp = node == NULL ? NULL : config_node_first ( node -> value ) ;
 for ( ;
 tmp != NULL ;
 tmp = config_node_next ( tmp ) ) {
 node = tmp -> data ;
 if ( node -> type != NODE_TYPE_KEY ) continue ;
 if ( len != 0 && g_ascii_strncasecmp ( node -> key , word , len ) != 0 ) continue ;
 list = g_list_append ( list , g_strdup ( node -> key ) ) ;
 }
 return list ;
 }