void TSHttpTxnClientKeepaliveSet ( TSHttpTxn txnp , int set ) {
 HttpSM * sm = ( HttpSM * ) txnp ;
 HttpTransact : : State * s = & ( sm -> t_state ) ;
 s -> hdr_info . trust_response_cl = ( set != 0 ) ;
 }