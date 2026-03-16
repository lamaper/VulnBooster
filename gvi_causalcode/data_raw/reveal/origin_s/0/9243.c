void TSFetchHeaderAdd ( TSFetchSM fetch_sm , const char * name , int name_len , const char * value , int value_len ) {
 sdk_assert ( sdk_sanity_check_fetch_sm ( fetch_sm ) == TS_SUCCESS ) ;
 ( ( FetchSM * ) fetch_sm ) -> ext_add_header ( name , name_len , value , value_len ) ;
 }