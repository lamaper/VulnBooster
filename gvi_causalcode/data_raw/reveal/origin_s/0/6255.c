int evdns_count_nameservers ( void ) {
 const struct nameserver * server = server_head ;
 int n = 0 ;
 if ( ! server ) return 0 ;
 do {
 ++ n ;
 server = server -> next ;
 }
 while ( server != server_head ) ;
 return n ;
 }