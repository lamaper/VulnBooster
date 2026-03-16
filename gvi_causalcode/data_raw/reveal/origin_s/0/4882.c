TSReturnCode TSCacheKeyDigestSet ( TSCacheKey key , const char * input , int length ) {
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_iocore_structure ( ( void * ) input ) == TS_SUCCESS ) ;
 sdk_assert ( length > 0 ) ;
 CacheInfo * ci = reinterpret_cast < CacheInfo * > ( key ) ;
 if ( ci -> magic != CACHE_INFO_MAGIC_ALIVE ) {
 return TS_ERROR ;
 }
 MD5Context ( ) . hash_immediate ( ci -> cache_key , input , length ) ;
 return TS_SUCCESS ;
 }