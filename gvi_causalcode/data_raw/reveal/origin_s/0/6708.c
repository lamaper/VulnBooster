void TSVConnCacheHttpInfoSet ( TSVConn connp , TSCacheHttpInfo infop ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( connp ) == TS_SUCCESS ) ;
 CacheVC * vc = ( CacheVC * ) connp ;
 if ( vc -> base_stat == cache_scan_active_stat ) {
 vc -> set_http_info ( ( CacheHTTPInfo * ) infop ) ;
 }
 }