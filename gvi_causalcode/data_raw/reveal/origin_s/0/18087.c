TSReturnCode sdk_sanity_check_txn ( TSHttpTxn txnp ) {
 if ( ( txnp != nullptr ) && ( ( ( HttpSM * ) txnp ) -> magic == HTTP_SM_MAGIC_ALIVE ) ) {
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }