int TSHttpCurrentClientConnectionsGet ( void ) {
 int64_t S ;
 HTTP_READ_DYN_SUM ( http_current_client_connections_stat , S ) ;
 return ( int ) S ;
 }