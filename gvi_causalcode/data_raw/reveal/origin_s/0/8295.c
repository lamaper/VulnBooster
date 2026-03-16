TSAction TSCacheScan ( TSCont contp , TSCacheKey key , int KB_per_second ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 INKContInternal * i = ( INKContInternal * ) contp ;
 if ( key ) {
 CacheInfo * info = ( CacheInfo * ) key ;
 return ( TSAction ) cacheProcessor . scan ( i , info -> hostname , info -> len , KB_per_second ) ;
 }
 return reinterpret_cast < TSAction > ( cacheProcessor . scan ( i , nullptr , 0 , KB_per_second ) ) ;
 }