static void search_reverse ( void ) {
 struct search_domain * cur , * prev = NULL , * next ;
 cur = global_search_state -> head ;
 while ( cur ) {
 next = cur -> next ;
 cur -> next = prev ;
 prev = cur ;
 cur = next ;
 }
 global_search_state -> head = prev ;
 }