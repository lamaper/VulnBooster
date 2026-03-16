TSReturnCode TSUuidCopy ( TSUuid dest , const TSUuid src ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) dest ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) src ) == TS_SUCCESS ) ;
 ATSUuid * d = ( ATSUuid * ) dest ;
 ATSUuid * s = ( ATSUuid * ) src ;
 if ( s -> valid ( ) ) {
 * d = * s ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }