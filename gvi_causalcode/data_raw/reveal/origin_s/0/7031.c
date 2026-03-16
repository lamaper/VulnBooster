TSReturnCode TSCacheKeyDestroy ( TSCacheKey key ) {
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 if ( ( ( CacheInfo * ) key ) -> magic != CACHE_INFO_MAGIC_ALIVE ) {
 return TS_ERROR ;
 }
 CacheInfo * i = ( CacheInfo * ) key ;
 ats_free ( i -> hostname ) ;
 i -> magic = CACHE_INFO_MAGIC_DEAD ;
 delete i ;
 return TS_SUCCESS ;
 }