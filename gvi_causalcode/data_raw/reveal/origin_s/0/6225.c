int evdns_resolve_reverse_ipv6 ( const struct in6_addr * in , int flags , evdns_callback_type callback , void * ptr ) {
 char buf [ 73 ] ;
 char * cp ;
 struct request * req ;
 int i ;
 assert ( in ) ;
 cp = buf ;
 for ( i = 15 ;
 i >= 0 ;
 -- i ) {
 u8 byte = in -> s6_addr [ i ] ;
 * cp ++ = "0123456789abcdef" [ byte & 0x0f ] ;
 * cp ++ = '.' ;
 * cp ++ = "0123456789abcdef" [ byte >> 4 ] ;
 * cp ++ = '.' ;
 }
 assert ( cp + strlen ( "ip6.arpa" ) < buf + sizeof ( buf ) ) ;
 memcpy ( cp , "ip6.arpa" , strlen ( "ip6.arpa" ) + 1 ) ;
 log ( EVDNS_LOG_DEBUG , "Resolve requested for %s (reverse)" , buf ) ;
 req = request_new ( TYPE_PTR , buf , flags , callback , ptr ) ;
 if ( ! req ) return 1 ;
 request_submit ( req ) ;
 return 0 ;
 }