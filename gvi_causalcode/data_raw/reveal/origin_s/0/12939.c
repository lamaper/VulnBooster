int TSHttpCurrentActiveClientConnectionsGet ( void ) {
 int64_t S ;
 HTTP_READ_DYN_SUM ( http_current_active_client_connections_stat , S ) ;
 return ( int ) S ;
 }