TSReturnCode TSHttpTxnServerPacketDscpSet ( TSHttpTxn txnp , int dscp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 if ( nullptr != sm -> ua_session ) {
 HttpServerSession * ssn = sm -> ua_session -> get_server_session ( ) ;
 if ( nullptr != ssn ) {
 NetVConnection * vc = ssn -> get_netvc ( ) ;
 if ( vc != nullptr ) {
 vc -> options . packet_tos = ( uint32_t ) dscp << 2 ;
 vc -> apply_options ( ) ;
 }
 }
 }
 TSHttpTxnConfigIntSet ( txnp , TS_CONFIG_NET_SOCK_PACKET_TOS_OUT , dscp << 2 ) ;
 return TS_SUCCESS ;
 }