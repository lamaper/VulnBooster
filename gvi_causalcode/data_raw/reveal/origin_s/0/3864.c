int evdns_nameserver_ip_add ( const char * ip_as_string ) {
 struct in_addr ina ;
 int port ;
 char buf [ 20 ] ;
 const char * cp ;
 cp = strchr ( ip_as_string , ':' ) ;
 if ( ! cp ) {
 cp = ip_as_string ;
 port = 53 ;
 }
 else {
 port = strtoint ( cp + 1 ) ;
 if ( port < 0 || port > 65535 ) {
 return 4 ;
 }
 if ( ( cp - ip_as_string ) >= ( int ) sizeof ( buf ) ) {
 return 4 ;
 }
 memcpy ( buf , ip_as_string , cp - ip_as_string ) ;
 buf [ cp - ip_as_string ] = '\0' ;
 cp = buf ;
 }
 if ( ! inet_aton ( cp , & ina ) ) {
 return 4 ;
 }
 return _evdns_nameserver_add_impl ( ina . s_addr , port ) ;
 }