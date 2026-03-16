static void sig_complete_target ( GList * * list , WINDOW_REC * window , const char * word , const char * line , int * want_space ) {
 const char * definition ;
 g_return_if_fail ( list != NULL ) ;
 g_return_if_fail ( word != NULL ) ;
 g_return_if_fail ( line != NULL ) ;
 if ( * line != '\0' ) {
 if ( ( definition = iconfig_get_str ( "conversions" , line , NULL ) ) != NULL ) {
 * list = g_list_append ( NULL , g_strdup ( definition ) ) ;
 signal_stop ( ) ;
 }
 }
 else {
 * list = completion_get_targets ( word ) ;
 if ( * list != NULL ) signal_stop ( ) ;
 }
 }