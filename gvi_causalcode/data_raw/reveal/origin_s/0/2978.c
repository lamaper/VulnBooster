TSReturnCode TSCacheReady ( int * is_ready ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) is_ready ) == TS_SUCCESS ) ;
 return TSCacheDataTypeReady ( TS_CACHE_DATA_TYPE_NONE , is_ready ) ;
 }