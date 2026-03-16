void TSHttpTxnServerIntercept ( TSCont contp , TSHttpTxn txnp ) {
 HttpSM * http_sm = ( HttpSM * ) txnp ;
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 http_sm -> plugin_tunnel_type = HTTP_PLUGIN_AS_SERVER ;
 http_sm -> plugin_tunnel = PluginVCCore : : alloc ( ( INKContInternal * ) contp ) ;
 }