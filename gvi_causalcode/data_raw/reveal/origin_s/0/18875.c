TSReturnCode TSHttpTxnServerFdGet ( TSHttpTxn txnp , int * fdp ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) fdp ) == TS_SUCCESS ) ;
 HttpSM * sm = reinterpret_cast < HttpSM * > ( txnp ) ;
 * fdp = - 1 ;
 HttpServerSession * ss = sm -> get_server_session ( ) ;
 if ( ss == nullptr ) {
 return TS_ERROR ;
 }
 NetVConnection * vc = ss -> get_netvc ( ) ;
 if ( vc == nullptr ) {
 return TS_ERROR ;
 }
 * fdp = vc -> get_socket ( ) ;
 return TS_SUCCESS ;
 }