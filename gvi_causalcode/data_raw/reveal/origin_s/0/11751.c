TSReturnCode TSCacheDataTypeReady ( TSCacheDataType type , int * is_ready ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) is_ready ) == TS_SUCCESS ) ;
 CacheFragType frag_type ;
 switch ( type ) {
 case TS_CACHE_DATA_TYPE_NONE : frag_type = CACHE_FRAG_TYPE_NONE ;
 break ;
 case TS_CACHE_DATA_TYPE_OTHER : case TS_CACHE_DATA_TYPE_HTTP : frag_type = CACHE_FRAG_TYPE_HTTP ;
 break ;
 default : * is_ready = 0 ;
 return TS_ERROR ;
 }
 * is_ready = cacheProcessor . IsCacheReady ( frag_type ) ;
 return TS_SUCCESS ;
 }