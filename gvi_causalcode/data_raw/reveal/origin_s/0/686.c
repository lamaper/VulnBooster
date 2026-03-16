TSUuidVersion TSUuidVersionGet ( TSUuid uuid ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) uuid ) == TS_SUCCESS ) ;
 ATSUuid * u = ( ATSUuid * ) uuid ;
 return u -> version ( ) ;
 }