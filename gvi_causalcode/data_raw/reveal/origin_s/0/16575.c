TSFetchSM TSFetchCreate ( TSCont contp , const char * method , const char * url , const char * version , struct sockaddr const * client_addr , int flags ) {
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( ats_is_ip ( client_addr ) ) ;
 FetchSM * fetch_sm = FetchSMAllocator . alloc ( ) ;
 fetch_sm -> ext_init ( ( Continuation * ) contp , method , url , version , client_addr , flags ) ;
 return ( TSFetchSM ) fetch_sm ;
 }