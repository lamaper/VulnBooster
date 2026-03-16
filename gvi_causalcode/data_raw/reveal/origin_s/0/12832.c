void TSTextLogObjectRollingIntervalSecSet ( TSTextLogObject the_object , int rolling_interval_sec ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( the_object ) == TS_SUCCESS ) ;
 ( ( TextLogObject * ) the_object ) -> set_rolling_interval_sec ( rolling_interval_sec ) ;
 }