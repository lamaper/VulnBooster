static GList * completion_joinlist ( GList * list1 , GList * list2 ) {
 GList * old ;
 old = list2 ;
 while ( list2 != NULL ) {
 if ( ! glist_find_icase_string ( list1 , list2 -> data ) ) list1 = g_list_append ( list1 , list2 -> data ) ;
 else g_free ( list2 -> data ) ;
 list2 = list2 -> next ;
 }
 g_list_free ( old ) ;
 return list1 ;
 }