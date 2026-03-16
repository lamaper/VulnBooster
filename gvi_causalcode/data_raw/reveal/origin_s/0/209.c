TSAction TSHostLookup ( TSCont contp , const char * hostname , size_t namelen ) {
 sdk_assert ( sdk_sanity_check_continuation ( contp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_null_ptr ( ( void * ) hostname ) == TS_SUCCESS ) ;
 sdk_assert ( namelen > 0 ) ;
 FORCE_PLUGIN_SCOPED_MUTEX ( contp ) ;
 INKContInternal * i = ( INKContInternal * ) contp ;
 return ( TSAction ) hostDBProcessor . getbyname_re ( i , hostname , namelen ) ;
 }