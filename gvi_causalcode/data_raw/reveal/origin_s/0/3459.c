TSAction TSCacheRemove ( TSCont contp , TSCacheKey key ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 CacheInfo * info = ( CacheInfo * ) key ;
 INKContInternal * i = ( INKContInternal * ) contp ;
 return ( TSAction ) cacheProcessor . remove ( i , & info -> cache_key , true , info -> frag_type , info -> hostname , info -> len ) ;
 }