TSReturnCode TSTextLogObjectDestroy ( TSTextLogObject the_object ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( the_object ) == TS_SUCCESS ) ;
 if ( Log : : config -> log_object_manager . unmanage_api_object ( ( TextLogObject * ) the_object ) ) {
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }