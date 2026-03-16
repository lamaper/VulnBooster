int evdns_resolve_reverse ( const struct in_addr * in , int flags , evdns_callback_type callback , void * ptr ) {
 char buf [ 32 ] ;
 struct request * req ;
 u32 a ;
 assert ( in ) ;
 a = ntohl ( in -> s_addr ) ;
 evutil_snprintf ( buf , sizeof ( buf ) , "%d.%d.%d.%d.in-addr.arpa" , ( int ) ( u8 ) ( ( a ) & 0xff ) , ( int ) ( u8 ) ( ( a >> 8 ) & 0xff ) , ( int ) ( u8 ) ( ( a >> 16 ) & 0xff ) , ( int ) ( u8 ) ( ( a >> 24 ) & 0xff ) ) ;
 log ( EVDNS_LOG_DEBUG , "Resolve requested for %s (reverse)" , buf ) ;
 req = request_new ( TYPE_PTR , buf , flags , callback , ptr ) ;
 if ( ! req ) return 1 ;
 request_submit ( req ) ;
 return 0 ;
 }