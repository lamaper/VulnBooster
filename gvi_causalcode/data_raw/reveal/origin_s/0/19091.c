TSReturnCode TSStringPercentDecode ( const char * str , size_t str_len , char * dst , size_t dst_size , size_t * length ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) str ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) dst ) == TS_SUCCESS ) ;
 if ( 0 == str_len ) {
 str_len = strlen ( str ) ;
 }
 char * buffer = dst ;
 const char * src = str ;
 int s = 0 ;
 unescape_str ( buffer , buffer + dst_size , src , src + str_len , s ) ;
 size_t data_written = std : : min < size_t > ( buffer - dst , dst_size - 1 ) ;
 * ( dst + data_written ) = '\0' ;
 if ( length ) {
 * length = ( data_written ) ;
 }
 return TS_SUCCESS ;
 }