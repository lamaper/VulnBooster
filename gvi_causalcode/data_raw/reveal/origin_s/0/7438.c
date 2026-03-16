void TSCacheHttpInfoSizeSet ( TSCacheHttpInfo infop , int64_t size ) {
 CacheHTTPInfo * info = ( CacheHTTPInfo * ) infop ;
 info -> object_size_set ( size ) ;
 }