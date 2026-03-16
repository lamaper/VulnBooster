TSReturnCode TSCacheKeyPinnedSet ( TSCacheKey key , time_t pin_in_cache ) {
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 if ( ( ( CacheInfo * ) key ) -> magic != CACHE_INFO_MAGIC_ALIVE ) {
 return TS_ERROR ;
 }
 CacheInfo * i = ( CacheInfo * ) key ;
 i -> pin_in_cache = pin_in_cache ;
 return TS_SUCCESS ;
 }