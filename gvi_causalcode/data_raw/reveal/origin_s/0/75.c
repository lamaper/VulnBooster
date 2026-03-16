char * TSMatcherReadIntoBuffer ( char * file_name , int * file_len ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) file_name ) == TS_SUCCESS ) ;
 return readIntoBuffer ( ( char * ) file_name , "TSMatcher" , file_len ) ;
 }