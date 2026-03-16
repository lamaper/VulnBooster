static void sig_message_own_public ( SERVER_REC * server , const char * msg , const char * target , const char * origtarget ) {
 CHANNEL_REC * channel ;
 NICK_REC * nick ;
 char * p , * msgnick ;
 g_return_if_fail ( server != NULL ) ;
 g_return_if_fail ( msg != NULL ) ;
 if ( target == NULL ) return ;
 channel = channel_find ( server , target ) ;
 if ( channel == NULL ) return ;
 p = strchr ( msg , ' ' ) ;
 if ( p != NULL && p != msg ) {
 msgnick = g_strndup ( msg , ( int ) ( p - msg ) ) ;
 nick = nicklist_find ( channel , msgnick ) ;
 if ( nick == NULL && msgnick [ 1 ] != '\0' ) {
 msgnick [ strlen ( msgnick ) - 1 ] = '\0' ;
 nick = nicklist_find ( channel , msgnick ) ;
 }
 g_free ( msgnick ) ;
 if ( nick != NULL && nick != channel -> ownnick ) CHANNEL_LAST_MSG_ADD ( channel , nick -> nick , TRUE ) ;
 }
 }