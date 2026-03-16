static void search_postfix_add ( const char * domain ) {
 int domain_len ;
 struct search_domain * sdomain ;
 while ( domain [ 0 ] == '.' ) domain ++ ;
 domain_len = strlen ( domain ) ;
 if ( ! global_search_state ) global_search_state = search_state_new ( ) ;
 if ( ! global_search_state ) return ;
 global_search_state -> num_domains ++ ;
 sdomain = ( struct search_domain * ) malloc ( sizeof ( struct search_domain ) + domain_len ) ;
 if ( ! sdomain ) return ;
 memcpy ( ( ( u8 * ) sdomain ) + sizeof ( struct search_domain ) , domain , domain_len ) ;
 sdomain -> next = global_search_state -> head ;
 sdomain -> len = domain_len ;
 global_search_state -> head = sdomain ;
 }