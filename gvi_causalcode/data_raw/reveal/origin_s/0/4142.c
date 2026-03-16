void TSUuidDestroy ( TSUuid uuid ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) uuid ) == TS_SUCCESS ) ;
 delete ( ATSUuid * ) uuid ;
 }