void TSCacheHttpInfoReqGet ( TSCacheHttpInfo infop , TSMBuffer * bufp , TSMLoc * obj ) {
 CacheHTTPInfo * info = ( CacheHTTPInfo * ) infop ;
 * ( reinterpret_cast < HTTPHdr * * > ( bufp ) ) = info -> request_get ( ) ;
 * obj = reinterpret_cast < TSMLoc > ( info -> request_get ( ) -> m_http ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( * bufp ) == TS_SUCCESS ) ;
 }