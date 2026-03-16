int TSHttpCurrentIdleClientConnectionsGet ( void ) {
 int64_t total = 0 ;
 int64_t active = 0 ;
 HTTP_READ_DYN_SUM ( http_current_client_connections_stat , total ) ;
 HTTP_READ_DYN_SUM ( http_current_active_client_connections_stat , active ) ;
 if ( total >= active ) {
 return ( int ) ( total - active ) ;
 }
 return 0 ;
 }