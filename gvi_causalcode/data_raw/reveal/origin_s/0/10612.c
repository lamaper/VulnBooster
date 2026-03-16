TSCacheKey TSCacheKeyCreate ( void ) {
 TSCacheKey key = ( TSCacheKey ) new CacheInfo ( ) ;
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 return key ;
 }