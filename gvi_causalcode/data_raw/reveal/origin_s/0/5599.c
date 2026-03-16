int TSHttpTxnIsInternal ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 return TSHttpSsnIsInternal ( TSHttpTxnSsnGet ( txnp ) ) ;
 }