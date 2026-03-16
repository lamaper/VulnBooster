TSReturnCode TSHttpTxnConfigFloatSet ( TSHttpTxn txnp , TSOverridableConfigKey conf , TSMgmtFloat value ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * s = reinterpret_cast < HttpSM * > ( txnp ) ;
 OverridableDataType type ;
 s -> t_state . setup_per_txn_configs ( ) ;
 TSMgmtFloat * dest = static_cast < TSMgmtFloat * > ( _conf_to_memberp ( conf , s -> t_state . txn_conf , & type ) ) ;
 if ( type != OVERRIDABLE_TYPE_FLOAT ) {
 return TS_ERROR ;
 }
 if ( dest ) {
 * dest = value ;
 return TS_SUCCESS ;
 }
 return TS_SUCCESS ;
 }