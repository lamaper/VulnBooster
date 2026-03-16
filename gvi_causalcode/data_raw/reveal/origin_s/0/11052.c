void TSTextLogObjectRollingOffsetHrSet ( TSTextLogObject the_object , int rolling_offset_hr ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( the_object ) == TS_SUCCESS ) ;
 ( ( TextLogObject * ) the_object ) -> set_rolling_offset_hr ( rolling_offset_hr ) ;
 }