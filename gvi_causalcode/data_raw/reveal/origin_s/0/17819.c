TSReturnCode TSHttpTxnConfigIntSet ( TSHttpTxn txnp , TSOverridableConfigKey conf , TSMgmtInt value ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * s = reinterpret_cast < HttpSM * > ( txnp ) ;
 OverridableDataType type ;
 s -> t_state . setup_per_txn_configs ( ) ;
 void * dest = _conf_to_memberp ( conf , s -> t_state . txn_conf , & type ) ;
 if ( ! dest ) {
 return TS_ERROR ;
 }
 switch ( type ) {
 case OVERRIDABLE_TYPE_INT : * ( static_cast < TSMgmtInt * > ( dest ) ) = value ;
 break ;
 case OVERRIDABLE_TYPE_BYTE : * ( static_cast < TSMgmtByte * > ( dest ) ) = static_cast < TSMgmtByte > ( value ) ;
 break ;
 default : return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }