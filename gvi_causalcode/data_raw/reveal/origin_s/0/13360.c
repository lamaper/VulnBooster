TSReturnCode TSHttpTxnConfigFloatGet ( TSHttpTxn txnp , TSOverridableConfigKey conf , TSMgmtFloat * value ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) value ) == TS_SUCCESS ) ;
 OverridableDataType type ;
 TSMgmtFloat * dest = static_cast < TSMgmtFloat * > ( _conf_to_memberp ( conf , ( ( HttpSM * ) txnp ) -> t_state . txn_conf , & type ) ) ;
 if ( type != OVERRIDABLE_TYPE_FLOAT ) {
 return TS_ERROR ;
 }
 if ( dest ) {
 * value = * dest ;
 return TS_SUCCESS ;
 }
 return TS_SUCCESS ;
 }