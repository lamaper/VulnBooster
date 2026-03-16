int evdns_set_option ( const char * option , const char * val , int flags ) {
 if ( ! strncmp ( option , "ndots:" , 6 ) ) {
 const int ndots = strtoint ( val ) ;
 if ( ndots == - 1 ) return - 1 ;
 if ( ! ( flags & DNS_OPTION_SEARCH ) ) return 0 ;
 log ( EVDNS_LOG_DEBUG , "Setting ndots to %d" , ndots ) ;
 if ( ! global_search_state ) global_search_state = search_state_new ( ) ;
 if ( ! global_search_state ) return - 1 ;
 global_search_state -> ndots = ndots ;
 }
 else if ( ! strncmp ( option , "timeout:" , 8 ) ) {
 const int timeout = strtoint ( val ) ;
 if ( timeout == - 1 ) return - 1 ;
 if ( ! ( flags & DNS_OPTION_MISC ) ) return 0 ;
 log ( EVDNS_LOG_DEBUG , "Setting timeout to %d" , timeout ) ;
 global_timeout . tv_sec = timeout ;
 }
 else if ( ! strncmp ( option , "max-timeouts:" , 12 ) ) {
 const int maxtimeout = strtoint_clipped ( val , 1 , 255 ) ;
 if ( maxtimeout == - 1 ) return - 1 ;
 if ( ! ( flags & DNS_OPTION_MISC ) ) return 0 ;
 log ( EVDNS_LOG_DEBUG , "Setting maximum allowed timeouts to %d" , maxtimeout ) ;
 global_max_nameserver_timeout = maxtimeout ;
 }
 else if ( ! strncmp ( option , "max-inflight:" , 13 ) ) {
 const int maxinflight = strtoint_clipped ( val , 1 , 65000 ) ;
 if ( maxinflight == - 1 ) return - 1 ;
 if ( ! ( flags & DNS_OPTION_MISC ) ) return 0 ;
 log ( EVDNS_LOG_DEBUG , "Setting maximum inflight requests to %d" , maxinflight ) ;
 global_max_requests_inflight = maxinflight ;
 }
 else if ( ! strncmp ( option , "attempts:" , 9 ) ) {
 int retries = strtoint ( val ) ;
 if ( retries == - 1 ) return - 1 ;
 if ( retries > 255 ) retries = 255 ;
 if ( ! ( flags & DNS_OPTION_MISC ) ) return 0 ;
 log ( EVDNS_LOG_DEBUG , "Setting retries to %d" , retries ) ;
 global_max_retransmits = retries ;
 }
 return 0 ;
 }