TSReturnCode TSUuidInitialize ( TSUuid uuid , TSUuidVersion v ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) uuid ) == TS_SUCCESS ) ;
 ATSUuid * u = ( ATSUuid * ) uuid ;
 u -> initialize ( v ) ;
 return u -> valid ( ) ? TS_SUCCESS : TS_ERROR ;
 }