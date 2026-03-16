static void last_msg_destroy ( GSList * * list , LAST_MSG_REC * rec ) {
 * list = g_slist_remove ( * list , rec ) ;
 g_free ( rec -> nick ) ;
 g_free ( rec ) ;
 }