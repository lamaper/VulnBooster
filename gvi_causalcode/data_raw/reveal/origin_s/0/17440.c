ssize_t TSFetchReadData ( TSFetchSM fetch_sm , void * buf , size_t len ) {
 sdk_assert ( sdk_sanity_check_fetch_sm ( fetch_sm ) == TS_SUCCESS ) ;
 return ( ( FetchSM * ) fetch_sm ) -> ext_read_data ( ( char * ) buf , len ) ;
 }