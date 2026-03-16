static void sig_complete_word ( GList * * list , WINDOW_REC * window , const char * word , const char * linestart , int * want_space ) {
 SERVER_REC * server ;
 CHANNEL_REC * channel ;
 QUERY_REC * query ;
 char * prefix ;
 g_return_if_fail ( list != NULL ) ;
 g_return_if_fail ( window != NULL ) ;
 g_return_if_fail ( word != NULL ) ;
 g_return_if_fail ( linestart != NULL ) ;
 server = window -> active_server ;
 if ( server == NULL && servers != NULL ) server = servers -> data ;
 if ( server != NULL && server_ischannel ( server , word ) ) {
 * list = completion_get_channels ( window -> active_server , word ) ;
 if ( * list != NULL ) signal_stop ( ) ;
 return ;
 }
 server = window -> active_server ;
 if ( server == NULL || ! server -> connected ) return ;
 if ( * linestart == '\0' && * word == '\0' ) {
 if ( ! completion_empty_line ) return ;
 prefix = g_strdup_printf ( "%cmsg" , * cmdchars ) ;
 * list = completion_msg ( server , NULL , "" , prefix ) ;
 if ( * list == NULL ) * list = g_list_append ( * list , g_strdup ( prefix ) ) ;
 g_free ( prefix ) ;
 signal_stop ( ) ;
 return ;
 }
 channel = CHANNEL ( window -> active ) ;
 query = QUERY ( window -> active ) ;
 if ( channel == NULL && query != NULL && g_ascii_strncasecmp ( word , query -> name , strlen ( word ) ) == 0 ) {
 * list = g_list_append ( * list , g_strdup ( query -> name ) ) ;
 }
 else if ( channel != NULL ) {
 const char * suffix = * linestart != '\0' ? NULL : completion_char ;
 complete_window_nicks ( list , window , word , suffix ) ;
 }
 else if ( window -> level & MSGLEVEL_MSGS ) {
 * list = g_list_concat ( completion_msg ( server , NULL , word , NULL ) , * list ) ;
 }
 if ( * list != NULL ) signal_stop ( ) ;
 }