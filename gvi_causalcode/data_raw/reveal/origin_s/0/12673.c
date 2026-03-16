void * TSFetchUserDataGet ( TSFetchSM fetch_sm ) {
 sdk_assert ( sdk_sanity_check_fetch_sm ( fetch_sm ) == TS_SUCCESS ) ;
 return ( ( FetchSM * ) fetch_sm ) -> ext_get_user_data ( ) ;
 }