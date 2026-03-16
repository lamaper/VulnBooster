void TSTextLogObjectHeaderSet ( TSTextLogObject the_object , const char * header ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( the_object ) == TS_SUCCESS ) ;
 ( ( TextLogObject * ) the_object ) -> set_log_file_header ( header ) ;
 }