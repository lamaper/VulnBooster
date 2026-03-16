int TSHttpCurrentServerConnectionsGet ( void ) {
 int64_t S ;
 HTTP_READ_GLOBAL_DYN_SUM ( http_current_server_connections_stat , S ) ;
 return ( int ) S ;
 }