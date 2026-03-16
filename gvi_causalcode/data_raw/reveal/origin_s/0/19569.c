static char * auto_complete ( CHANNEL_REC * channel , const char * line ) {
 GList * comp ;
 const char * p ;
 char * nick , * ret ;
 p = strstr ( line , completion_char ) ;
 if ( p == NULL ) return NULL ;
 nick = g_strndup ( line , ( int ) ( p - line ) ) ;
 ret = NULL ;
 if ( nicklist_find ( channel , nick ) == NULL ) {
 comp = completion_channel_nicks ( channel , nick , NULL ) ;
 if ( comp != NULL ) {
 ret = g_strconcat ( comp -> data , p , NULL ) ;
 g_list_foreach ( comp , ( GFunc ) g_free , NULL ) ;
 g_list_free ( comp ) ;
 }
 }
 g_free ( nick ) ;
 return ret ;
 }