time_t TSCacheHttpInfoReqSentTimeGet ( TSCacheHttpInfo infop ) {
 CacheHTTPInfo * info = ( CacheHTTPInfo * ) infop ;
 return info -> request_sent_time_get ( ) ;
 }