TSReturnCode TSHttpTxnClientPacketTosSet ( TSHttpTxn txnp , int tos ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 if ( nullptr == sm -> ua_session ) {
 return TS_ERROR ;
 }
 NetVConnection * vc = sm -> ua_session -> get_netvc ( ) ;
 if ( nullptr == vc ) {
 return TS_ERROR ;
 }
 vc -> options . packet_tos = ( uint32_t ) tos ;
 vc -> apply_options ( ) ;
 return TS_SUCCESS ;
 }