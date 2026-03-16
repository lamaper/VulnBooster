static void resolv_conf_parse_line ( char * const start , int flags ) {
 char * strtok_state ;
 static const char * const delims = " \t" ;

 if ( ! first_token ) return ;
 if ( ! strcmp ( first_token , "nameserver" ) && ( flags & DNS_OPTION_NAMESERVERS ) ) {
 const char * const nameserver = NEXT_TOKEN ;
 struct in_addr ina ;
 if ( inet_aton ( nameserver , & ina ) ) {
 evdns_nameserver_add ( ina . s_addr ) ;
 }
 }
 else if ( ! strcmp ( first_token , "domain" ) && ( flags & DNS_OPTION_SEARCH ) ) {
 const char * const domain = NEXT_TOKEN ;
 if ( domain ) {
 search_postfix_clear ( ) ;
 search_postfix_add ( domain ) ;
 }
 }
 else if ( ! strcmp ( first_token , "search" ) && ( flags & DNS_OPTION_SEARCH ) ) {
 const char * domain ;
 search_postfix_clear ( ) ;
 while ( ( domain = NEXT_TOKEN ) ) {
 search_postfix_add ( domain ) ;
 }
 search_reverse ( ) ;
 }
 else if ( ! strcmp ( first_token , "options" ) ) {
 const char * option ;
 while ( ( option = NEXT_TOKEN ) ) {
 const char * val = strchr ( option , ':' ) ;
 evdns_set_option ( option , val ? val + 1 : "" , flags ) ;
 }
 }
