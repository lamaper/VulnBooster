void TSTextLogObjectFlush ( TSTextLogObject the_object ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( the_object ) == TS_SUCCESS ) ;
 ( ( TextLogObject * ) the_object ) -> force_new_buffer ( ) ;
 }