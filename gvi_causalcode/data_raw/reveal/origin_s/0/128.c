static GList * convert_msglist ( GSList * msglist ) {
 GList * list ;
 list = NULL ;
 while ( msglist != NULL ) {
 LAST_MSG_REC * rec = msglist -> data ;
 list = g_list_append ( list , rec -> nick ) ;
 msglist = g_slist_remove ( msglist , rec ) ;
 g_free ( rec ) ;
 }
 return list ;
 }