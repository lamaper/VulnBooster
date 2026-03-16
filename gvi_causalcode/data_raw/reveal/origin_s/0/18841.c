static void sig_complete_connect ( GList * * list , WINDOW_REC * window , const char * word , const char * line , int * want_space ) {
 g_return_if_fail ( list != NULL ) ;
 g_return_if_fail ( word != NULL ) ;
 * list = completion_get_chatnets ( word ) ;
 * list = g_list_concat ( * list , completion_get_servers ( word ) ) ;
 if ( * list != NULL ) signal_stop ( ) ;
 }