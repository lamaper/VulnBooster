void TSFetchUserDataSet ( TSFetchSM fetch_sm , void * data ) {
 sdk_assert ( sdk_sanity_check_fetch_sm ( fetch_sm ) == TS_SUCCESS ) ;
 ( ( FetchSM * ) fetch_sm ) -> ext_set_user_data ( data ) ;
 }