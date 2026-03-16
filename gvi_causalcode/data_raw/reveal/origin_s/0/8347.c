int TSHttpTxnIsCacheable ( TSHttpTxn txnp , TSMBuffer request , TSMBuffer response ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HTTPHdr * req , * resp ;
 if ( request ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( request ) == TS_SUCCESS ) ;
 req = reinterpret_cast < HTTPHdr * > ( request ) ;
 }
 else {
 req = & ( sm -> t_state . hdr_info . client_request ) ;
 }
 if ( response ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( response ) == TS_SUCCESS ) ;
 resp = reinterpret_cast < HTTPHdr * > ( response ) ;
 }
 else {
 resp = & ( sm -> t_state . hdr_info . server_response ) ;
 }
 return ( req -> valid ( ) && resp -> valid ( ) && HttpTransact : : is_response_cacheable ( & ( sm -> t_state ) , req , resp ) ) ? 1 : 0 ;
 }