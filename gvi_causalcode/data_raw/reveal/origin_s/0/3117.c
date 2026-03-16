TSReturnCode TSHttpTxnServerPacketTosSet ( TSHttpTxn txnp , int tos ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 if ( nullptr != sm -> ua_session ) {
 HttpServerSession * ssn = sm -> ua_session -> get_server_session ( ) ;
 if ( nullptr != ssn ) {
 NetVConnection * vc = ssn -> get_netvc ( ) ;
 if ( vc != nullptr ) {
 vc -> options . packet_tos = ( uint32_t ) tos ;
 vc -> apply_options ( ) ;
 }
 }
 }
 TSHttpTxnConfigIntSet ( txnp , TS_CONFIG_NET_SOCK_PACKET_TOS_OUT , tos ) ;
 return TS_SUCCESS ;
 }