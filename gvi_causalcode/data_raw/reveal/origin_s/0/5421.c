const char * TSUuidStringGet ( const TSUuid uuid ) {
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) uuid ) == TS_SUCCESS ) ;
 ATSUuid * u = ( ATSUuid * ) ( uuid ) ;
 if ( u -> valid ( ) ) {
 return u -> getString ( ) ;
 }
 return nullptr ;
 }