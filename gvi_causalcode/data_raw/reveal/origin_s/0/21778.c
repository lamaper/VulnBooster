static void sdk_free_field_handle ( TSMBuffer bufp , MIMEFieldSDKHandle * field_handle ) {
 if ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) {
 mHandleAllocator . free ( field_handle ) ;
 }
 }