static int search_request_new ( int type , const char * const name , int flags , evdns_callback_type user_callback , void * user_arg ) {
 assert ( type == TYPE_A || type == TYPE_AAAA ) ;
 if ( ( ( flags & DNS_QUERY_NO_SEARCH ) == 0 ) && global_search_state && global_search_state -> num_domains ) {
 struct request * req ;
 if ( string_num_dots ( name ) >= global_search_state -> ndots ) {
 req = request_new ( type , name , flags , user_callback , user_arg ) ;
 if ( ! req ) return 1 ;
 req -> search_index = - 1 ;
 }
 else {
 char * const new_name = search_make_new ( global_search_state , 0 , name ) ;
 if ( ! new_name ) return 1 ;
 req = request_new ( type , new_name , flags , user_callback , user_arg ) ;
 free ( new_name ) ;
 if ( ! req ) return 1 ;
 req -> search_index = 0 ;
 }
 req -> search_origname = strdup ( name ) ;
 req -> search_state = global_search_state ;
 req -> search_flags = flags ;
 global_search_state -> refcount ++ ;
 request_submit ( req ) ;
 return 0 ;
 }
 else {
 struct request * const req = request_new ( type , name , flags , user_callback , user_arg ) ;
 if ( ! req ) return 1 ;
 request_submit ( req ) ;
 return 0 ;
 }
 }