TSReturnCode TSClientRequestUuidGet ( TSHttpTxn txnp , char * uuid_str ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) uuid_str ) == TS_SUCCESS ) ;
 HttpSM * sm = ( HttpSM * ) txnp ;
 const char * machine = ( char * ) Machine : : instance ( ) -> uuid . getString ( ) ;
 int len ;
 len = snprintf ( uuid_str , TS_CRUUID_STRING_LEN , "%s-%" PRId64 "" , machine , sm -> sm_id ) ;
 if ( len > TS_CRUUID_STRING_LEN ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }