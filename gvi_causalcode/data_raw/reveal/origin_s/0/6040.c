int evdns_resolv_conf_parse ( int flags , const char * const filename ) {
 struct stat st ;
 int fd , n , r ;
 u8 * resolv ;
 char * start ;
 int err = 0 ;
 log ( EVDNS_LOG_DEBUG , "Parsing resolv.conf file %s" , filename ) ;
 fd = open ( filename , O_RDONLY ) ;
 if ( fd < 0 ) {
 evdns_resolv_set_defaults ( flags ) ;
 return 1 ;
 }
 if ( fstat ( fd , & st ) ) {
 err = 2 ;
 goto out1 ;
 }
 if ( ! st . st_size ) {
 evdns_resolv_set_defaults ( flags ) ;
 err = ( flags & DNS_OPTION_NAMESERVERS ) ? 6 : 0 ;
 goto out1 ;
 }
 if ( st . st_size > 65535 ) {
 err = 3 ;
 goto out1 ;
 }
 resolv = ( u8 * ) malloc ( ( size_t ) st . st_size + 1 ) ;
 if ( ! resolv ) {
 err = 4 ;
 goto out1 ;
 }
 n = 0 ;
 while ( ( r = read ( fd , resolv + n , ( size_t ) st . st_size - n ) ) > 0 ) {
 n += r ;
 if ( n == st . st_size ) break ;
 assert ( n < st . st_size ) ;
 }
 if ( r < 0 ) {
 err = 5 ;
 goto out2 ;
 }
 resolv [ n ] = 0 ;
 start = ( char * ) resolv ;
 for ( ;
 ;
 ) {
 char * const newline = strchr ( start , '\n' ) ;
 if ( ! newline ) {
 resolv_conf_parse_line ( start , flags ) ;
 break ;
 }
 else {
 * newline = 0 ;
 resolv_conf_parse_line ( start , flags ) ;
 start = newline + 1 ;
 }
 }
 if ( ! server_head && ( flags & DNS_OPTION_NAMESERVERS ) ) {
 evdns_nameserver_ip_add ( "127.0.0.1" ) ;
 err = 6 ;
 }
 if ( flags & DNS_OPTION_SEARCH && ( ! global_search_state || global_search_state -> num_domains == 0 ) ) {
 search_set_from_hostname ( ) ;
 }
 out2 : free ( resolv ) ;
 out1 : close ( fd ) ;
 return err ;
 }