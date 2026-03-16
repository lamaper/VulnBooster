static void sig_complete_window ( GList * * list , WINDOW_REC * window , const char * word , const char * linestart , int * want_space ) {
 WINDOW_REC * win ;
 WI_ITEM_REC * item ;
 GSList * tmp ;
 int len ;
 g_return_if_fail ( list != NULL ) ;
 g_return_if_fail ( word != NULL ) ;
 len = strlen ( word ) ;
 for ( tmp = windows ;
 tmp != NULL ;
 tmp = tmp -> next ) {
 win = tmp -> data ;
 item = win -> active ;
 if ( win -> name != NULL && g_ascii_strncasecmp ( win -> name , word , len ) == 0 ) * list = g_list_append ( * list , g_strdup ( win -> name ) ) ;
 if ( item != NULL && g_ascii_strncasecmp ( item -> visible_name , word , len ) == 0 ) * list = g_list_append ( * list , g_strdup ( item -> visible_name ) ) ;
 }
 if ( * list != NULL ) signal_stop ( ) ;
 }