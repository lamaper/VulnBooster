char * TSMatcherTokLine ( char * buffer , char * * last ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) buffer ) == TS_SUCCESS ) ;
 return tokLine ( buffer , last ) ;
 }