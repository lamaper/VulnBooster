void * TSContDataGet ( TSCont contp ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 INKContInternal * i = ( INKContInternal * ) contp ;
 return i -> mdata ;
 }