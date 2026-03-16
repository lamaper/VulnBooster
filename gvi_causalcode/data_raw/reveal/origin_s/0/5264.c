void TSMatcherLineDestroy ( TSMatcherLine ml ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) ml ) == TS_SUCCESS ) ;
 ats_free ( ml ) ;
 }