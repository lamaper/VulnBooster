static void search_postfix_clear ( void ) {
 search_state_decref ( global_search_state ) ;
 global_search_state = search_state_new ( ) ;
 }