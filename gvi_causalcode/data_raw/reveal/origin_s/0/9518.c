TSReturnCode TSCacheKeyDigestFromUrlSet ( TSCacheKey key , TSMLoc url ) {
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 if ( ( ( CacheInfo * ) key ) -> magic != CACHE_INFO_MAGIC_ALIVE ) {
 return TS_ERROR ;
 }
 url_MD5_get ( ( URLImpl * ) url , & ( ( CacheInfo * ) key ) -> cache_key ) ;
 return TS_SUCCESS ;
 }