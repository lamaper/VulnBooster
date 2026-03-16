int TSMimeHdrFieldEqual ( TSMBuffer bufp , TSMLoc hdr_obj , TSMLoc field1_obj , TSMLoc field2_obj ) {
 sdk_assert ( sdk_sanity_check_mbuffer ( bufp ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field1_obj , hdr_obj ) == TS_SUCCESS ) ;
 sdk_assert ( sdk_sanity_check_field_handle ( field2_obj , hdr_obj ) == TS_SUCCESS ) ;
 MIMEFieldSDKHandle * field1_handle = ( MIMEFieldSDKHandle * ) field1_obj ;
 MIMEFieldSDKHandle * field2_handle = ( MIMEFieldSDKHandle * ) field2_obj ;
 if ( ( field1_handle == nullptr ) || ( field2_handle == nullptr ) ) {
 return ( field1_handle == field2_handle ) ;
 }
 return ( field1_handle -> field_ptr == field2_handle -> field_ptr ) ;
 }