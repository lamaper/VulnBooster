void TSHttpTxnErrorBodySet ( TSHttpTxn txnp , char * buf , size_t buflength , char * mimetype ) {
 sdk_assert ( sdk_sanity_check_txn ( txnp ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 s -> free_internal_msg_buffer ( ) ;
 ats_free ( s -> internal_msg_buffer_type ) ;
 s -> internal_msg_buffer = buf ;
 s -> internal_msg_buffer_size = buf ? buflength : 0 ;
 s -> internal_msg_buffer_fast_allocator_size = - 1 ;
 s -> internal_msg_buffer_type = mimetype ;
 }