static void last_msg_add ( GSList * * list , const char * nick , int own , int max ) {
 LAST_MSG_REC * rec ;
 if ( max <= 0 ) return ;
 rec = last_msg_find ( * list , nick ) ;
 if ( rec != NULL ) {
 * list = g_slist_remove ( * list , rec ) ;
 if ( own ) rec -> own = max ;
 else if ( rec -> own ) rec -> own -- ;
 }
 else {
 rec = g_new ( LAST_MSG_REC , 1 ) ;
 rec -> nick = g_strdup ( nick ) ;
 while ( ( int ) g_slist_length ( * list ) >= max ) {
 last_msg_destroy ( list , g_slist_last ( * list ) -> data ) ;
 }
 rec -> own = own ? max : 0 ;
 }
 rec -> time = time ( NULL ) ;
 last_msg_dec_owns ( * list ) ;
 * list = g_slist_prepend ( * list , rec ) ;
 }