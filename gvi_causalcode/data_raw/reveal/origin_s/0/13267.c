int TSHttpCurrentCacheConnectionsGet ( void ) {
 int64_t S ;
 HTTP_READ_DYN_SUM ( http_current_cache_connections_stat , S ) ;
 return ( int ) S ;
 }