static SERVER_REC * line_get_server ( const char * line ) {
 SERVER_REC * server ;
 char * tag , * ptr ;
 g_return_val_if_fail ( line != NULL , NULL ) ;
 if ( * line != '-' ) return NULL ;
 tag = g_strdup ( line + 1 ) ;
 ptr = strchr ( tag , ' ' ) ;
 if ( ptr != NULL ) * ptr = '\0' ;
 server = server_find_tag ( tag ) ;
 g_free ( tag ) ;
 return server ;
 }