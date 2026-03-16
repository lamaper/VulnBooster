static void sig_complete_msg ( GList * * list , WINDOW_REC * window , const char * word , const char * line , int * want_space ) {
 SERVER_REC * server , * msgserver ;
 g_return_if_fail ( list != NULL ) ;
 g_return_if_fail ( word != NULL ) ;
 g_return_if_fail ( line != NULL ) ;
 server = window -> active_server ;
 if ( server == NULL || ! server -> connected ) return ;
 msgserver = line_get_server ( line ) ;
 * list = completion_msg ( server , msgserver , word , NULL ) ;
 if ( CHANNEL ( window -> active ) != NULL ) complete_window_nicks ( list , window , word , NULL ) ;
 if ( * list != NULL ) signal_stop ( ) ;
 }