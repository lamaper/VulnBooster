int evdns_resolve_ipv4 ( const char * name , int flags , evdns_callback_type callback , void * ptr ) {
 log ( EVDNS_LOG_DEBUG , "Resolve requested for %s" , name ) ;
 if ( flags & DNS_QUERY_NO_SEARCH ) {
 struct request * const req = request_new ( TYPE_A , name , flags , callback , ptr ) ;
 if ( req == NULL ) return ( 1 ) ;
 request_submit ( req ) ;
 return ( 0 ) ;
 }
 else {
 return ( search_request_new ( TYPE_A , name , flags , callback , ptr ) ) ;
 }
 }