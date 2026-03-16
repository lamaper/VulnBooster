TSReturnCode TSHttpTxnCachedRespGet ( TSHttpTxn txnp , TSMBuffer * bufp , TSMLoc * obj ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) obj ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HTTPInfo * cached_obj = sm -> t_state . cache_info . object_read ;
 if ( ( ! cached_obj ) || ( ! cached_obj -> valid ( ) ) ) {
 return TS_ERROR ;
 }
 HTTPHdr * cached_hdr = sm -> t_state . cache_info . object_read -> response_get ( ) ;
 if ( ! cached_hdr -> valid ( ) ) {
 return TS_ERROR ;
 }
 HdrHeapSDKHandle * * handle = & ( sm -> t_state . cache_resp_hdr_heap_handle ) ;
 if ( * handle == nullptr ) {
 * handle = ( HdrHeapSDKHandle * ) sm -> t_state . arena . alloc ( sizeof ( HdrHeapSDKHandle ) ) ;
 ( * handle ) -> m_heap = cached_hdr -> m_heap ;
 }
 * ( reinterpret_cast < HdrHeapSDKHandle * * > ( bufp ) ) = * handle ;
 * obj = reinterpret_cast < TSMLoc > ( cached_hdr -> m_http ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( * bufp ) == TS_SUCCESS ) ;
 return TS_SUCCESS ;
 }