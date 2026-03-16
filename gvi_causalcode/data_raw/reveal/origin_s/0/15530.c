void TSHttpTxnServerRequestBodySet ( TSHttpTxn txnp , char * buf , int64_t buflength ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 s -> free_internal_msg_buffer ( ) ;
 if ( buf ) {
 s -> api_server_request_body_set = true ;
 s -> internal_msg_buffer = buf ;
 s -> internal_msg_buffer_size = buflength ;
 }
 else {
 s -> api_server_request_body_set = false ;
 s -> internal_msg_buffer = nullptr ;
 s -> internal_msg_buffer_size = 0 ;
 }
 s -> internal_msg_buffer_fast_allocator_size = - 1 ;
 }