TSReturnCode TSTextLogObjectRollingEnabledSet ( TSTextLogObject the_object , int rolling_enabled ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( the_object ) == TS_SUCCESS ) ;
 if ( LogRollingEnabledIsValid ( rolling_enabled ) ) {
 ( ( TextLogObject * ) the_object ) -> set_rolling_enabled ( ( Log : : RollingEnabledValues ) rolling_enabled ) ;
 return TS_SUCCESS ;
 }
 return TS_ERROR ;
 }