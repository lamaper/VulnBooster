TSCacheHttpInfo TSCacheHttpInfoCopy ( TSCacheHttpInfo infop ) {
 CacheHTTPInfo * new_info = new CacheHTTPInfo ;
 new_info -> copy ( ( CacheHTTPInfo * ) infop ) ;
 return reinterpret_cast < TSCacheHttpInfo > ( new_info ) ;
 }