TSReturnCode TSUuidStringParse ( TSUuid uuid , const char * str ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) uuid ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) str ) == TS_SUCCESS ) ;
 ATSUuid * u = ( ATSUuid * ) uuid ;
 if ( u -> parseString ( str ) ) {
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }