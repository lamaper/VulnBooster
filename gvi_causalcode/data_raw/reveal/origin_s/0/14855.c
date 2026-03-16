int64_t TSCacheHttpInfoSizeGet ( TSCacheHttpInfo infop ) {
 CacheHTTPInfo * info = ( CacheHTTPInfo * ) infop ;
 return info -> object_size_get ( ) ;
 }