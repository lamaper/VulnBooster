static int evdns_request_len ( const int name_len ) {
 return 96 + name_len + 2 + 4 ;
 }