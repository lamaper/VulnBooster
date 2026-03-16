TSHttpSsn TSHttpTxnSsnGet ( TSHttpTxn txnp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 return reinterpret_cast < TSHttpSsn > ( sm -> ua_session ? ( TSHttpSsn ) sm -> ua_session -> get_parent ( ) : nullptr ) ;
 }