TSAction TSCacheRead ( TSCont contp , TSCacheKey key ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 CacheInfo * info = ( CacheInfo * ) key ;
 Continuation * i = ( INKContInternal * ) contp ;
 return ( TSAction ) cacheProcessor . open_read ( i , & info -> cache_key , true , info -> frag_type , info -> hostname , info -> len ) ;
 }