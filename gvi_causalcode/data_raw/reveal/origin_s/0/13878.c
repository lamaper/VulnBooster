TSReturnCode sdk_sanity_check_null_ptr ( void * ptr ) {
 if ( ptr == nullptr ) {
 return TS_ERROR ;
 }
 return TS_SUCCESS ;
 }