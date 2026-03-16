static void sig_complete_topic ( GList * * list , WINDOW_REC * window , const char * word , const char * line , int * want_space ) {
 const char * topic ;
 g_return_if_fail ( list != NULL ) ;
 g_return_if_fail ( word != NULL ) ;
 if ( * word == '\0' && IS_CHANNEL ( window -> active ) ) {
 topic = CHANNEL ( window -> active ) -> topic ;
 if ( topic != NULL ) {
 * list = g_list_append ( NULL , g_strdup ( topic ) ) ;
 signal_stop ( ) ;
 }
 }
 }