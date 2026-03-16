TSAction TSCacheWrite ( TSCont contp , TSCacheKey key ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 CacheInfo * info = ( CacheInfo * ) key ;
 Continuation * i = ( INKContInternal * ) contp ;
 return ( TSAction ) cacheProcessor . open_write ( i , & info -> cache_key , true , info -> frag_type , 0 , false , info -> pin_in_cache , info -> hostname , info -> len ) ;
 }