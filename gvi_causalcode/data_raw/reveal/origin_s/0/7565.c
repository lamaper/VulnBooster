TSReturnCode TSStringPercentEncode ( const char * str , int str_len , char * dst , size_t dst_size , size_t * length , const unsigned char * map ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) str ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) dst ) == TS_SUCCESS ) ;
 int new_len ;
 if ( str_len < 0 ) {
 str_len = strlen ( str ) ;
 }
 sdk_assert ( str_len < static_cast < int > ( dst_size ) ) ;
 if ( nullptr == LogUtils : : pure_escapify_url ( nullptr , const_cast < char * > ( str ) , str_len , & new_len , dst , dst_size , map ) ) {
 if ( length ) {
 * length = 0 ;
 }
 return TS_ERROR ;
 }
 if ( length ) {
 * length = new_len ;
 }
 return TS_SUCCESS ;
 }