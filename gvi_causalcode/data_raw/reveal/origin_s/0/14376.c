void TSHttpTxnOverwriteExpireTime ( TSHttpTxn txnp , time_t expire_time ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpTransact : : State * s = & ( ( ( HttpSM * ) txnp ) -> t_state ) ;
 s -> plugin_set_expire_time = expire_time ;
 }