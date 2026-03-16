inline TSReturnCode sdk_sanity_check_cachekey ( TSCacheKey key ) {
 if ( nullptr == key ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }