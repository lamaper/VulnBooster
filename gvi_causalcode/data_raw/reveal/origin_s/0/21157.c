void TSHttpTxnArgSet ( TSHttpTxn txnp , int arg_idx , void * arg ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 sdk_assert ( arg_idx >= 0 && arg_idx < HTTP_SSN_TXN_MAX_USER_ARG ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 sm -> t_state . user_args [ arg_idx ] = arg ;
 }