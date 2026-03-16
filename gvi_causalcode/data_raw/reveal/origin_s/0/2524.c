static int search_try_next ( struct request * const req ) {
 if ( req -> search_state ) {
 char * new_name ;
 struct request * newreq ;
 req -> search_index ++ ;
 if ( req -> search_index >= req -> search_state -> num_domains ) {
 if ( string_num_dots ( req -> search_origname ) < req -> search_state -> ndots ) {
 newreq = request_new ( req -> request_type , req -> search_origname , req -> search_flags , req -> user_callback , req -> user_pointer ) ;
 log ( EVDNS_LOG_DEBUG , "Search: trying raw query %s" , req -> search_origname ) ;
 if ( newreq ) {
 request_submit ( newreq ) ;
 return 0 ;
 }
 }
 return 1 ;
 }
 new_name = search_make_new ( req -> search_state , req -> search_index , req -> search_origname ) ;
 if ( ! new_name ) return 1 ;
 log ( EVDNS_LOG_DEBUG , "Search: now trying %s (%d)" , new_name , req -> search_index ) ;
 newreq = request_new ( req -> request_type , new_name , req -> search_flags , req -> user_callback , req -> user_pointer ) ;
 free ( new_name ) ;
 if ( ! newreq ) return 1 ;
 newreq -> search_origname = req -> search_origname ;
 req -> search_origname = NULL ;
 newreq -> search_state = req -> search_state ;
 newreq -> search_flags = req -> search_flags ;
 newreq -> search_index = req -> search_index ;
 newreq -> search_state -> refcount ++ ;
 request_submit ( newreq ) ;
 return 0 ;
 }
 return 1 ;
 }