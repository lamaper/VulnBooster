void TSFetchDestroy ( TSFetchSM fetch_sm ) {
 sdk_assert ( sdk_sanity_check_fetch_sm ( fetch_sm ) == TS_SUCCESS ) ;
 ( ( FetchSM * ) fetch_sm ) -> ext_destroy ( ) ;
 }