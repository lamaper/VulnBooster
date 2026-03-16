const char * TSHttpTxnPluginTagGet ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 return sm -> plugin_tag ;
 }