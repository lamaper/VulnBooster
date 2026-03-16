TSReturnCode TSCacheKeyDataTypeSet ( TSCacheKey key , TSCacheDataType type ) {
 sdk_assert ( sdk_sanity_check_cachekey ( key ) == TS_SUCCESS ) ;
 if ( ( ( CacheInfo * ) key ) -> magic != CACHE_INFO_MAGIC_ALIVE ) {
 return TS_ERROR ;
 }
 switch ( type ) {
 case TS_CACHE_DATA_TYPE_NONE : ( ( CacheInfo * ) key ) -> frag_type = CACHE_FRAG_TYPE_NONE ;
 break ;
 case TS_CACHE_DATA_TYPE_OTHER : case TS_CACHE_DATA_TYPE_HTTP : ( ( CacheInfo * ) key ) -> frag_type = CACHE_FRAG_TYPE_HTTP ;
 break ;
 default : return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }