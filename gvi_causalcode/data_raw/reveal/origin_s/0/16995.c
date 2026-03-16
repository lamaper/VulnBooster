void TSFetchWriteData ( TSFetchSM fetch_sm , const void * data , size_t len ) {
 sdk_assert ( sdk_sanity_check_fetch_sm ( fetch_sm ) == TS_SUCCESS ) ;
 ( ( FetchSM * ) fetch_sm ) -> ext_write_data ( data , len ) ;
 }