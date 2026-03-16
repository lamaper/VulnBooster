void TSTextLogObjectRollingSizeMbSet ( TSTextLogObject the_object , int rolling_size_mb ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( the_object ) == TS_SUCCESS ) ;
 ( ( TextLogObject * ) the_object ) -> set_rolling_size_mb ( rolling_size_mb ) ;
 }