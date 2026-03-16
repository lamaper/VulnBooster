static void evdns_resolv_set_defaults ( int flags ) {
 if ( flags & DNS_OPTION_SEARCH ) search_set_from_hostname ( ) ;
 if ( flags & DNS_OPTION_NAMESERVERS ) evdns_nameserver_ip_add ( "127.0.0.1" ) ;
 }