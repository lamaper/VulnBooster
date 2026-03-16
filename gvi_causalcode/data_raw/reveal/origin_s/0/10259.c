static void event_text ( const char * data , SERVER_REC * server , WI_ITEM_REC * item ) {
 char * line , * str , * target ;
 g_return_if_fail ( data != NULL ) ;
 if ( item == NULL ) return ;
 if ( * data == '\0' ) {
 signal_stop ( ) ;
 return ;
 }
 line = settings_get_bool ( "expand_escapes" ) ? expand_escapes ( data , server , item ) : g_strdup ( data ) ;
 if ( completion_auto && IS_CHANNEL ( item ) ) {
 str = auto_complete ( CHANNEL ( item ) , line ) ;
 if ( str != NULL ) {
 g_free ( line ) ;
 line = str ;
 }
 }
 target = escape_string ( window_item_get_target ( item ) ) ;
 str = g_strdup_printf ( IS_CHANNEL ( item ) ? "-channel \"%s\" %s" : IS_QUERY ( item ) ? "-nick \"%s\" %s" : "%s %s" , target , line ) ;
 g_free ( target ) ;
 signal_emit ( "command msg" , 3 , str , server , item ) ;
 g_free ( str ) ;
 g_free ( line ) ;
 signal_stop ( ) ;
 }