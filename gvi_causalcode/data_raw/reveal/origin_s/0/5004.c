TSReturnCode TSBase64Decode ( const char * str , size_t str_len , unsigned char * dst , size_t dst_size , size_t * length ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) str ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) dst ) == TS_SUCCESS ) ;
 return ats_base64_decode ( str , str_len , dst , dst_size , length ) ? TS_SUCCESS : TS_ERROR ;
 }