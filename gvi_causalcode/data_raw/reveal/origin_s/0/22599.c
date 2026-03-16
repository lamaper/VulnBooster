int evhttp_add_header ( struct evkeyvalq * headers , const char * key , const char * value ) {
 event_debug ( ( "%s: key: %s val: %s\n" , __func__ , key , value ) ) ;
 if ( strchr ( key , '\r' ) != NULL || strchr ( key , '\n' ) != NULL ) {
 event_debug ( ( "%s: dropping illegal header key\n" , __func__ ) ) ;
 return ( - 1 ) ;
 }
 if ( ! evhttp_header_is_valid_value ( value ) ) {
 event_debug ( ( "%s: dropping illegal header value\n" , __func__ ) ) ;
 return ( - 1 ) ;
 }
 return ( evhttp_add_header_internal ( headers , key , value ) ) ;
 }