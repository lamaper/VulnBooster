void TSHttpTxnSetHttpRetStatus ( TSHttpTxn txnp , TSHttpStatus http_retstatus ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> t_state . http_return_code = ( HTTPStatus ) http_retstatus ;
 }