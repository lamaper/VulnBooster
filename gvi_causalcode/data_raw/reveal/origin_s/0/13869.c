void do_outgoing_connection ( connection_t * c ) {
 struct addrinfo * proxyai = NULL ;
 int result ;
 if ( ! c -> outgoing ) {
 logger ( LOG_ERR , "do_outgoing_connection() for %s called without c->outgoing" , c -> name ) ;
 abort ( ) ;
 }
 begin : if ( ! c -> outgoing -> ai ) {
 if ( ! c -> outgoing -> cfg ) {
 ifdebug ( CONNECTIONS ) logger ( LOG_ERR , "Could not set up a meta connection to %s" , c -> name ) ;
 c -> status . remove = true ;
 retry_outgoing ( c -> outgoing ) ;
 c -> outgoing = NULL ;
 return ;
 }
 char * address , * port , * space ;
 get_config_string ( c -> outgoing -> cfg , & address ) ;
 space = strchr ( address , ' ' ) ;
 if ( space ) {
 port = xstrdup ( space + 1 ) ;
 * space = 0 ;
 }
 else {
 if ( ! get_config_string ( lookup_config ( c -> config_tree , "Port" ) , & port ) ) {
 port = xstrdup ( "655" ) ;
 }
 }
 c -> outgoing -> ai = str2addrinfo ( address , port , SOCK_STREAM ) ;
 if ( ! c -> outgoing -> ai && proxytype != PROXY_NONE && is_valid_host_port ( address , port ) ) {
 memset ( & c -> address , 0 , sizeof ( c -> address ) ) ;
 c -> address . sa . sa_family = AF_UNKNOWN ;
 c -> address . unknown . address = address ;
 c -> address . unknown . port = port ;
 }
 else {
 free ( address ) ;
 free ( port ) ;
 }
 c -> outgoing -> aip = c -> outgoing -> ai ;
 c -> outgoing -> cfg = lookup_config_next ( c -> config_tree , c -> outgoing -> cfg ) ;
 if ( ! c -> outgoing -> ai && proxytype != PROXY_NONE ) {
 goto connect ;
 }
 }
 if ( ! c -> outgoing -> aip ) {
 if ( c -> outgoing -> ai ) {
 freeaddrinfo ( c -> outgoing -> ai ) ;
 }
 c -> outgoing -> ai = NULL ;
 goto begin ;
 }
 memcpy ( & c -> address , c -> outgoing -> aip -> ai_addr , c -> outgoing -> aip -> ai_addrlen ) ;
 c -> outgoing -> aip = c -> outgoing -> aip -> ai_next ;
 connect : if ( c -> hostname ) {
 free ( c -> hostname ) ;
 }
 c -> hostname = sockaddr2hostname ( & c -> address ) ;
 ifdebug ( CONNECTIONS ) logger ( LOG_INFO , "Trying to connect to %s (%s)" , c -> name , c -> hostname ) ;
 if ( ! proxytype ) {
 c -> socket = socket ( c -> address . sa . sa_family , SOCK_STREAM , IPPROTO_TCP ) ;
 }
 else if ( proxytype == PROXY_EXEC ) {
 c -> status . proxy_passed = true ;
 do_outgoing_pipe ( c , proxyhost ) ;
 }
 else {
 proxyai = str2addrinfo ( proxyhost , proxyport , SOCK_STREAM ) ;
 if ( ! proxyai ) {
 goto begin ;
 }
 ifdebug ( CONNECTIONS ) logger ( LOG_INFO , "Using proxy at %s port %s" , proxyhost , proxyport ) ;
 c -> socket = socket ( proxyai -> ai_family , SOCK_STREAM , IPPROTO_TCP ) ;
 }
 if ( c -> socket == - 1 ) {
 ifdebug ( CONNECTIONS ) logger ( LOG_ERR , "Creating socket for %s failed: %s" , c -> hostname , sockstrerror ( sockerrno ) ) ;
 goto begin ;
 }
 if ( proxytype != PROXY_EXEC ) {
 configure_tcp ( c ) ;
 }



 if ( c -> address . sa . sa_family == AF_INET6 ) {
 setsockopt ( c -> socket , IPPROTO_IPV6 , IPV6_V6ONLY , ( void * ) & option , sizeof ( option ) ) ;
 }

 int b = - 1 ;
 for ( int i = 0 ;
 i < listen_sockets ;
 i ++ ) {
 if ( listen_socket [ i ] . sa . sa . sa_family == c -> address . sa . sa_family ) {
 if ( b == - 1 ) {
 b = i ;
 }
 else {
 b = - 1 ;
 break ;
 }
 }
 }
 if ( b != - 1 ) {
 sockaddr_t sa = listen_socket [ b ] . sa ;
 if ( sa . sa . sa_family == AF_INET ) {
 sa . in . sin_port = 0 ;
 }
 else if ( sa . sa . sa_family == AF_INET6 ) {
 sa . in6 . sin6_port = 0 ;
 }
 if ( bind ( c -> socket , & sa . sa , SALEN ( sa . sa ) ) ) {
 char * addrstr = sockaddr2hostname ( & sa ) ;
 logger ( LOG_ERR , "Can't bind to %s/tcp: %s" , addrstr , sockstrerror ( sockerrno ) ) ;
 free ( addrstr ) ;
 }
 }
 }
 if ( ! proxytype ) {
 result = connect ( c -> socket , & c -> address . sa , SALEN ( c -> address . sa ) ) ;
 }
 else if ( proxytype == PROXY_EXEC ) {
 result = 0 ;
 }
 else {
 result = connect ( c -> socket , proxyai -> ai_addr , proxyai -> ai_addrlen ) ;
 freeaddrinfo ( proxyai ) ;
 }
 now = time ( NULL ) ;
 if ( result == - 1 ) {
 if ( sockinprogress ( sockerrno ) ) {
 c -> last_ping_time = now ;
 c -> status . connecting = true ;
 return ;
 }
 closesocket ( c -> socket ) ;
 ifdebug ( CONNECTIONS ) logger ( LOG_ERR , "%s: %s" , c -> hostname , sockstrerror ( sockerrno ) ) ;
 goto begin ;
 }
 finish_connecting ( c ) ;
 return ;
 }