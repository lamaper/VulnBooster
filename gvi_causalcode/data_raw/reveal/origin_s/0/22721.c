TSReturnCode TSHttpTxnClientFdGet ( TSHttpTxn txnp , int * fdp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) fdp ) == TS_SUCCESS ) ;
 TSHttpSsn ssnp = TSHttpTxnSsnGet ( txnp ) ;
 return TSHttpSsnClientFdGet ( ssnp , fdp ) ;
 }