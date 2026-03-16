time_t TSCacheHttpInfoRespReceivedTimeGet ( TSCacheHttpInfo infop ) {
 CacheHTTPInfo * info = ( CacheHTTPInfo * ) infop ;
 return info -> response_received_time_get ( ) ;
 }