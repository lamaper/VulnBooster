TSReturnCode TSHttpTxnOutgoingTransparencySet ( TSHttpTxn txnp , int flag ) {
 if ( TS_SUCCESS != sdk_sanity_check_txn ( txnp ) ) {
 return TS_ERROR ;
 }
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 if ( nullptr == sm || nullptr == sm -> ua_session ) {
 return TS_ERROR ;
 }
 sm -> ua_session -> set_outbound_transparent ( flag ) ;
 return TS_SUCCESS ;
 }