TSVConn TSTransformCreate ( TSEventFunc event_funcp , TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 return TSVConnCreate ( event_funcp , TSContMutexGet ( reinterpret_cast < TSCont > ( txnp ) ) ) ;
 }