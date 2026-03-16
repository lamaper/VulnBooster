char * TSMatcherExtractIPRange ( char * match_str , sockaddr * addr1 , sockaddr * addr2 ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) match_str ) == TS_SUCCESS ) ;
 return ( char * ) ExtractIpRange ( match_str , addr1 , addr2 ) ;
 }