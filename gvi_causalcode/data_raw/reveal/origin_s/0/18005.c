void TSContDataSet ( TSCont contp , void * data ) {
 sdk_assert ( sdk_sanity_check_iocore_structure ( contp ) == TS_SUCCESS ) ;
 INKContInternal * i = ( INKContInternal * ) contp ;
 i -> mdata = data ;
 }