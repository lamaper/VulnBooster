TSReturnCode TSHttpTxnParentSelectionUrlGet ( TSHttpTxn txnp , TSMBuffer bufp , TSMLoc obj ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_url_handle ( obj ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 URL u , * l_url ;
 u . m_heap = ( ( HdrHeapSDKHandle * ) bufp ) -> m_heap ;
 u . m_url_impl = ( URLImpl * ) obj ;
 if ( ! u . valid ( ) ) return TS_ERROR ;
 l_url = sm -> t_state . cache_info . parent_selection_url ;
 if ( l_url && l_url -> valid ( ) ) {
 u . copy ( l_url ) ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }