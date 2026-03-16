int evdns_nameserver_add ( unsigned long int address ) {
 return _evdns_nameserver_add_impl ( address , 53 ) ;
 }