TSReturnCode TSHttpTxnConfigIntGet ( TSHttpTxn txnp , TSOverridableConfigKey conf , TSMgmtInt * value ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) value ) == TS_SUCCESS ) ;
 HttpSM * s = reinterpret_cast < HttpSM * > ( txnp ) ;
 OverridableDataType type ;
 void * src = _conf_to_memberp ( conf , s -> t_state . txn_conf , & type ) ;
 if ( ! src ) {
 return TS_ERROR ;
 }
 switch ( type ) {
 case OVERRIDABLE_TYPE_INT : * value = * ( static_cast < TSMgmtInt * > ( src ) ) ;
 break ;
 case OVERRIDABLE_TYPE_BYTE : * value = * ( static_cast < TSMgmtByte * > ( src ) ) ;
 break ;
 default : return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }