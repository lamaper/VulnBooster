static void sig_complete_away ( GList * * list , WINDOW_REC * window , const char * word , const char * line , int * want_space ) {
 const char * reason ;
 g_return_if_fail ( list != NULL ) ;
 g_return_if_fail ( word != NULL ) ;
 * want_space = FALSE ;
 if ( * word == '\0' && window -> active_server != NULL ) {
 reason = SERVER ( window -> active_server ) -> away_reason ;
 if ( reason != NULL ) {
 * list = g_list_append ( NULL , g_strdup ( reason ) ) ;
 signal_stop ( ) ;
 }
 }
 }