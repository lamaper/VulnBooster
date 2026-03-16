void TSMgmtUpdateRegister ( TSCont contp , const char * plugin_name ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) plugin_name ) == TS_SUCCESS ) ;
 global_config_cbs -> insert ( ( INKContInternal * ) contp , plugin_name ) ;
 }