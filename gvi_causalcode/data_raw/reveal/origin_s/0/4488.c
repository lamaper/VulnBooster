TSReturnCode TSStatFindName ( const char * name , int * idp ) {
 int id ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) name ) == TS_SUCCESS ) ;
 if ( RecGetRecordOrderAndId ( name , nullptr , & id ) != REC_ERR_OKAY ) {
 return TS_ERROR ;
 }
 if ( RecGetGlobalRawStatPtr ( api_rsb , id ) == nullptr ) {
 return TS_ERROR ;
 }
 * idp = id ;
 return TS_SUCCESS ;
 }