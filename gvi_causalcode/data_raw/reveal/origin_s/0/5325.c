TSReturnCode TSCacheKeyHostNameSet ( TSCacheKey key , const char * hostname , int host_len ) {
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) hostname ) == TS_SUCCESS ) ;
 sdk_assert ( host_len > 0 ) ;
 if ( ( ( CacheInfo * ) key ) -> magic != CACHE_INFO_MAGIC_ALIVE ) {
 return TS_ERROR ;
 }
 CacheInfo * i = ( CacheInfo * ) key ;
 i -> hostname = ( char * ) ats_malloc ( host_len ) ;
 memcpy ( i -> hostname , hostname , host_len ) ;
 i -> len = host_len ;
 return TS_SUCCESS ;
 }