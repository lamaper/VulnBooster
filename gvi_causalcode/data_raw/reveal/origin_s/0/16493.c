int64_t TSVConnCacheObjectSizeGet ( TSVConn connp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 CacheVC * vc = ( CacheVC * ) connp ;
 return vc -> get_object_size ( ) ;
 }