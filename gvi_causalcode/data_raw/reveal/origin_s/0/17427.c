inline static void update_cache_control_information_from_config ( HttpTransact : : State * s ) {
 getCacheControl ( & s -> cache_control , & s -> request_data , s -> txn_conf ) ;
 s -> cache_info . directives . does_config_permit_lookup &= ( s -> cache_control . never_cache == false ) ;
 s -> cache_info . directives . does_config_permit_storing &= ( s -> cache_control . never_cache == false ) ;
 s -> cache_info . directives . does_client_permit_storing = HttpTransact : : does_client_request_permit_storing ( & s -> cache_control , & s -> hdr_info . client_request ) ;
 s -> cache_info . directives . does_client_permit_lookup = HttpTransact : : does_client_request_permit_cached_response ( s -> txn_conf , & s -> cache_control , & s -> hdr_info . client_request , s -> via_string ) ;
 s -> cache_info . directives . does_client_permit_dns_storing = HttpTransact : : does_client_request_permit_dns_caching ( & s -> cache_control , & s -> hdr_info . client_request ) ;
 if ( s -> client_info . http_version == HTTPVersion ( 0 , 9 ) ) {
 s -> cache_info . directives . does_client_permit_lookup = false ;
 s -> cache_info . directives . does_client_permit_storing = false ;
 }
 if ( s -> cache_control . cache_responses_to_cookies >= 0 ) {
 s -> txn_conf -> cache_responses_to_cookies = s -> cache_control . cache_responses_to_cookies ;
 }
 }