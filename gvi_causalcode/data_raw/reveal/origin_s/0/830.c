REGRESSION_TEST ( SDK_API_TSHttpHdr ) ( RegressionTest * test , int , int * pstatus ) {
 TSMBuffer bufp1 = ( TSMBuffer ) nullptr ;
 TSMBuffer bufp2 = ( TSMBuffer ) nullptr ;
 TSMBuffer bufp3 = ( TSMBuffer ) nullptr ;
 TSMBuffer bufp4 = ( TSMBuffer ) nullptr ;
 TSMLoc hdr_loc1 = ( TSMLoc ) nullptr ;
 TSMLoc hdr_loc2 = ( TSMLoc ) nullptr ;
 TSMLoc hdr_loc3 = ( TSMLoc ) nullptr ;
 TSMLoc hdr_loc4 = ( TSMLoc ) nullptr ;
 TSHttpType hdr1type ;
 TSHttpType hdr2type ;
 const char * methodGet ;
 TSMLoc url_loc ;
 TSMLoc url_loc_Get ;
 const char * url_host = "www.example.com" ;
 int url_port = 2345 ;
 const char * url_path = "abcd/efg/hij.htm" ;
 const char * response_reason = "aefa" ;
 const char * response_reason_get ;
 TSHttpStatus status_get ;
 int version_major = 2 ;
 int version_minor = 1 ;
 int version_get ;
 const char * method1 ;
 const char * method2 ;
 int length1 ;
 int length2 ;
 TSMLoc url_loc1 ;
 TSMLoc url_loc2 ;
 int length ;
 const char * expected_iobuf = "GET http://www.example.com:2345/abcd/efg/hij.htm HTTP/2.1\r\n\r\n" ;
 int actual_length ;
 int expected_length ;
 bool test_passed_Http_Hdr_Create = false ;
 bool test_passed_Http_Hdr_Type = false ;
 bool test_passed_Http_Hdr_Method = false ;
 bool test_passed_Http_Hdr_Url = false ;
 bool test_passed_Http_Hdr_Status = false ;
 bool test_passed_Http_Hdr_Reason = false ;
 bool test_passed_Http_Hdr_Reason_Lookup = false ;
 bool test_passed_Http_Hdr_Version = false ;
 bool test_passed_Http_Hdr_Copy = false ;
 bool test_passed_Http_Hdr_Clone = false ;
 bool test_passed_Http_Hdr_Length = false ;
 bool test_passed_Http_Hdr_Print = false ;
 bool test_passed_Http_Hdr_Destroy = false ;
 bool try_print_function = true ;
 bool test_buffer_created = true ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 bufp1 = TSMBufferCreate ( ) ;
 bufp2 = TSMBufferCreate ( ) ;
 bufp3 = TSMBufferCreate ( ) ;
 bufp4 = TSMBufferCreate ( ) ;
 if ( test_buffer_created == true ) {
 hdr_loc1 = TSHttpHdrCreate ( bufp1 ) ;
 hdr_loc2 = TSHttpHdrCreate ( bufp2 ) ;
 hdr_loc3 = TSHttpHdrCreate ( bufp3 ) ;
 SDK_RPRINT ( test , "TSHttpHdrCreate" , "TestCase1&2&3" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Create = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrCreate" , "All Test Cases" , TC_FAIL , "Cannot run test as unable to allocate MBuffers" ) ;
 }
 if ( test_passed_Http_Hdr_Create == true ) {
 if ( ( TSHttpHdrTypeSet ( bufp1 , hdr_loc1 , TS_HTTP_TYPE_REQUEST ) == TS_ERROR ) || ( TSHttpHdrTypeSet ( bufp2 , hdr_loc2 , TS_HTTP_TYPE_RESPONSE ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSHttpHdrTypeSet" , "TestCase1|2" , TC_FAIL , "TSHttpHdrTypeSet returns TS_ERROR" ) ;
 }
 else {
 hdr1type = TSHttpHdrTypeGet ( bufp1 , hdr_loc1 ) ;
 hdr2type = TSHttpHdrTypeGet ( bufp2 , hdr_loc2 ) ;
 if ( ( hdr1type == TS_HTTP_TYPE_REQUEST ) && ( hdr2type == TS_HTTP_TYPE_RESPONSE ) ) {
 SDK_RPRINT ( test , "TSHttpHdrTypeSet&Get" , "TestCase1&2" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Type = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrTypeSet&Get" , "TestCase1&2" , TC_FAIL , "Values mismatch" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrTypeSet&Get" , "All Test Case" , TC_FAIL , "Cannot run test as Header Creation Test failed" ) ;
 }
 if ( test_passed_Http_Hdr_Type == true ) {
 if ( TSHttpHdrMethodSet ( bufp1 , hdr_loc1 , TS_HTTP_METHOD_GET , - 1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrMethodSet&Get" , "TestCase1" , TC_FAIL , "TSHttpHdrMethodSet returns TS_ERROR" ) ;
 }
 else {
 methodGet = TSHttpHdrMethodGet ( bufp1 , hdr_loc1 , & length ) ;
 if ( ( strncmp ( methodGet , TS_HTTP_METHOD_GET , length ) == 0 ) && ( length == ( int ) strlen ( TS_HTTP_METHOD_GET ) ) ) {
 SDK_RPRINT ( test , "TSHttpHdrMethodSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Method = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrMethodSet&Get" , "TestCase1" , TC_FAIL , "Value's mismatch" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrMethodSet&Get" , "All Test Case" , TC_FAIL , "Cannot run test as Header's Type cannot be set" ) ;
 }
 if ( test_passed_Http_Hdr_Type == true ) {
 if ( TSUrlCreate ( bufp1 , & url_loc ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSHttpHdrUrlSet&Get" , "TestCase1" , TC_FAIL , "Cannot run test as TSUrlCreate returns TS_ERROR" ) ;
 }
 else {
 if ( TSHttpHdrUrlSet ( bufp1 , hdr_loc1 , url_loc ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrUrlSet&Get" , "TestCase1" , TC_FAIL , "TSHttpHdrUrlSet returns TS_ERROR" ) ;
 }
 else {
 if ( TSHttpHdrUrlGet ( bufp1 , hdr_loc1 , & url_loc_Get ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSHttpHdrUrlSet&Get" , "TestCase1" , TC_FAIL , "TSHttpHdrUrlGet retuns TS_ERROR" ) ;
 }
 else {
 if ( url_loc == url_loc_Get ) {
 SDK_RPRINT ( test , "TSHttpHdrUrlSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Url = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrUrlSet&Get" , "TestCase1" , TC_FAIL , "Value's mismatch" ) ;
 }
 if ( TSHandleMLocRelease ( bufp1 , hdr_loc1 , url_loc_Get ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "" , TC_FAIL , "Unable to release handle to URL" ) ;
 }
 }
 }
 if ( TSUrlSchemeSet ( bufp1 , url_loc , TS_URL_SCHEME_HTTP , - 1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSUrlSchemeSet" , "" , TC_FAIL , "Unable to set scheme in URL in the HTTP Header" ) ;
 try_print_function = false ;
 }
 if ( TSUrlHostSet ( bufp1 , url_loc , url_host , - 1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSUrlHostSet" , "" , TC_FAIL , "Unable to set host in URL in the HTTP Header" ) ;
 try_print_function = false ;
 }
 if ( TSUrlPortSet ( bufp1 , url_loc , url_port ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSUrlPortSet" , "" , TC_FAIL , "Unable to set port in URL in the HTTP Header" ) ;
 try_print_function = false ;
 }
 if ( TSUrlPathSet ( bufp1 , url_loc , url_path , - 1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSUrlPathSet" , "" , TC_FAIL , "Unable to set path in URL in the HTTP Header" ) ;
 try_print_function = false ;
 }
 if ( TSHandleMLocRelease ( bufp1 , hdr_loc1 , url_loc ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "" , TC_FAIL , "Unable to release handle to URL" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrUrlSet&Get" , "All Test Case" , TC_FAIL , "Cannot run test as Header's Type cannot be set" ) ;
 }
 if ( test_passed_Http_Hdr_Type == true ) {
 if ( TSHttpHdrReasonSet ( bufp2 , hdr_loc2 , response_reason , - 1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrReasonSet&Get" , "TestCase1" , TC_FAIL , "TSHttpHdrReasonSet returns TS_ERROR" ) ;
 }
 else {
 response_reason_get = TSHttpHdrReasonGet ( bufp2 , hdr_loc2 , & length ) ;
 if ( ( strncmp ( response_reason_get , response_reason , length ) == 0 ) && ( length == ( int ) strlen ( response_reason ) ) ) {
 SDK_RPRINT ( test , "TSHttpHdrReasonSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Reason = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrReasonSet&Get" , "TestCase1" , TC_FAIL , "Value's mismatch" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrReasonSet&Get" , "All Test Case" , TC_FAIL , "Cannot run test as Header's Type cannot be set" ) ;
 }
 if ( test_passed_Http_Hdr_Type == true ) {
 if ( TSHttpHdrStatusSet ( bufp2 , hdr_loc2 , TS_HTTP_STATUS_OK ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrStatusSet&Get" , "TestCase1" , TC_FAIL , "TSHttpHdrStatusSet returns TS_ERROR" ) ;
 }
 else {
 status_get = TSHttpHdrStatusGet ( bufp2 , hdr_loc2 ) ;
 if ( status_get == TS_HTTP_STATUS_OK ) {
 SDK_RPRINT ( test , "TSHttpHdrStatusSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Status = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrStatusSet&Get" , "TestCase1" , TC_FAIL , "Value's mismatch" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrStatusSet&Get" , "All Test Case" , TC_FAIL , "Cannot run test as Header's Type cannot be set" ) ;
 }
 if ( test_passed_Http_Hdr_Type == true ) {
 if ( TSHttpHdrVersionSet ( bufp1 , hdr_loc1 , TS_HTTP_VERSION ( version_major , version_minor ) ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrVersionSet&Get" , "TestCase1" , TC_FAIL , "TSHttpHdrVersionSet returns TS_ERROR" ) ;
 }
 else {
 version_get = TSHttpHdrVersionGet ( bufp1 , hdr_loc1 ) ;
 if ( ( version_major == TS_HTTP_MAJOR ( version_get ) ) && ( version_minor == TS_HTTP_MINOR ( version_get ) ) ) {
 SDK_RPRINT ( test , "TSHttpHdrVersionSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Version = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrVersionSet&Get" , "TestCase1" , TC_FAIL , "Value's mismatch" ) ;
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrVersionSet&Get" , "All Test Case" , TC_FAIL , "Cannot run test as Header's Type cannot be set" ) ;
 }
 if ( test_passed_Http_Hdr_Version == true ) {
 if ( TSHttpHdrVersionSet ( bufp2 , hdr_loc2 , TS_HTTP_VERSION ( version_major , version_minor ) ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrVersionSet&Get" , "TestCase2" , TC_FAIL , "TSHttpHdrVersionSet returns TS_ERROR" ) ;
 test_passed_Http_Hdr_Version = false ;
 }
 else {
 version_get = TSHttpHdrVersionGet ( bufp2 , hdr_loc2 ) ;
 if ( ( version_major == TS_HTTP_MAJOR ( version_get ) ) && ( version_minor == TS_HTTP_MINOR ( version_get ) ) ) {
 SDK_RPRINT ( test , "TSHttpHdrVersionSet&Get" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrVersionSet&Get" , "TestCase2" , TC_FAIL , "Value's mismatch" ) ;
 test_passed_Http_Hdr_Version = false ;
 }
 }
 }
 if ( strcmp ( "None" , TSHttpHdrReasonLookup ( TS_HTTP_STATUS_NONE ) ) != 0 ) {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase1" , TC_FAIL , "TSHttpHdrReasonLookup returns Value's mismatch" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Reason_Lookup = true ;
 }
 if ( strcmp ( "OK" , TSHttpHdrReasonLookup ( TS_HTTP_STATUS_OK ) ) != 0 ) {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase2" , TC_FAIL , "TSHttpHdrReasonLookup returns Value's mismatch" ) ;
 if ( test_passed_Http_Hdr_Reason_Lookup == true ) {
 test_passed_Http_Hdr_Reason_Lookup = false ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 if ( strcmp ( "Continue" , TSHttpHdrReasonLookup ( TS_HTTP_STATUS_CONTINUE ) ) != 0 ) {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase3" , TC_FAIL , "TSHttpHdrReasonLookup returns Value's mismatch" ) ;
 if ( test_passed_Http_Hdr_Reason_Lookup == true ) {
 test_passed_Http_Hdr_Reason_Lookup = false ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase3" , TC_PASS , "ok" ) ;
 }
 if ( strcmp ( "Not Modified" , TSHttpHdrReasonLookup ( TS_HTTP_STATUS_NOT_MODIFIED ) ) != 0 ) {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase4" , TC_FAIL , "TSHttpHdrReasonLookup returns Value's mismatch" ) ;
 if ( test_passed_Http_Hdr_Reason_Lookup == true ) {
 test_passed_Http_Hdr_Reason_Lookup = false ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase4" , TC_PASS , "ok" ) ;
 }
 if ( strcmp ( "Early Hints" , TSHttpHdrReasonLookup ( TS_HTTP_STATUS_EARLY_HINTS ) ) != 0 ) {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase5" , TC_FAIL , "TSHttpHdrReasonLookup returns Value's mismatch" ) ;
 if ( test_passed_Http_Hdr_Reason_Lookup == true ) {
 test_passed_Http_Hdr_Reason_Lookup = false ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrReasonLookup" , "TestCase5" , TC_PASS , "ok" ) ;
 }
 if ( test_passed_Http_Hdr_Create == true ) {
 if ( TSHttpHdrCopy ( bufp3 , hdr_loc3 , bufp1 , hdr_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "TSHttpHdrCopy returns TS_ERROR" ) ;
 }
 else {
 bool flag = true ;
 if ( flag == true ) {
 TSHttpType type1 = TSHttpHdrTypeGet ( bufp1 , hdr_loc1 ) ;
 TSHttpType type2 = TSHttpHdrTypeGet ( bufp3 , hdr_loc3 ) ;
 if ( type1 != type2 ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Type mismatch in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 int version1 = TSHttpHdrVersionGet ( bufp1 , hdr_loc1 ) ;
 int version2 = TSHttpHdrVersionGet ( bufp3 , hdr_loc3 ) ;
 if ( version1 != version2 ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Version mismatch in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 method1 = TSHttpHdrMethodGet ( bufp1 , hdr_loc1 , & length1 ) ;
 method2 = TSHttpHdrMethodGet ( bufp3 , hdr_loc3 , & length2 ) ;
 if ( ( length1 != length2 ) || ( strncmp ( method1 , method2 , length1 ) != 0 ) ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Method mismatch in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 if ( ( TSHttpHdrUrlGet ( bufp1 , hdr_loc1 , & url_loc1 ) != TS_SUCCESS ) || ( TSHttpHdrUrlGet ( bufp3 , hdr_loc3 , & url_loc2 ) != TS_SUCCESS ) ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "TSHttpVersionGet returns TS_ERROR" ) ;
 }
 else {
 const char * scheme1 ;
 const char * scheme2 ;
 const char * host1 ;
 const char * host2 ;
 int port1 ;
 int port2 ;
 const char * path1 ;
 const char * path2 ;
 scheme1 = TSUrlSchemeGet ( bufp1 , url_loc1 , & length1 ) ;
 scheme2 = TSUrlSchemeGet ( bufp3 , url_loc2 , & length2 ) ;
 if ( ( length1 != length2 ) || ( strncmp ( scheme1 , scheme2 , length1 ) != 0 ) ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Url Scheme has different values in both headers" ) ;
 flag = false ;
 }
 if ( flag == true ) {
 host1 = TSUrlHostGet ( bufp1 , url_loc1 , & length1 ) ;
 host2 = TSUrlHostGet ( bufp3 , url_loc2 , & length2 ) ;
 if ( ( length1 != length2 ) || ( strncmp ( host1 , host2 , length1 ) != 0 ) ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Url Host has different values in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 port1 = TSUrlPortGet ( bufp1 , url_loc1 ) ;
 port2 = TSUrlPortGet ( bufp3 , url_loc2 ) ;
 if ( port1 != port2 ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Url Port has different values in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 path1 = TSUrlPathGet ( bufp1 , url_loc1 , & length1 ) ;
 path2 = TSUrlPathGet ( bufp3 , url_loc2 , & length2 ) ;
 if ( ( path1 != nullptr ) && ( path2 != nullptr ) ) {
 if ( ( length1 != length2 ) || ( strncmp ( path1 , path2 , length1 ) != 0 ) ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Url Path has different values in both headers" ) ;
 flag = false ;
 }
 }
 else {
 if ( path1 != path2 ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Url Host has different values in both headers" ) ;
 flag = false ;
 }
 }
 if ( ( TSHandleMLocRelease ( bufp1 , hdr_loc1 , url_loc1 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp3 , hdr_loc3 , url_loc2 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "" , TC_FAIL , "Unable to release Handle acquired by TSHttpHdrUrlGet" ) ;
 }
 }
 if ( flag == true ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Copy = true ;
 }
 }
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "All Test Cases" , TC_PASS , "Cannot run test as TSHttpHdrCreate has failed" ) ;
 }
 if ( test_passed_Http_Hdr_Create == true ) {
 if ( TSHttpHdrClone ( bufp4 , bufp1 , hdr_loc1 , & hdr_loc4 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_FAIL , "TSHttpHdrClone returns TS_ERROR" ) ;
 }
 else {
 bool flag = true ;
 if ( flag == true ) {
 TSHttpType type1 = TSHttpHdrTypeGet ( bufp1 , hdr_loc1 ) ;
 TSHttpType type2 = TSHttpHdrTypeGet ( bufp4 , hdr_loc4 ) ;
 if ( type1 != type2 ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_FAIL , "Type mismatch in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 int version1 = TSHttpHdrVersionGet ( bufp1 , hdr_loc1 ) ;
 int version2 = TSHttpHdrVersionGet ( bufp4 , hdr_loc4 ) ;
 if ( version1 != version2 ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_FAIL , "Version mismatch in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 method1 = TSHttpHdrMethodGet ( bufp1 , hdr_loc1 , & length1 ) ;
 method2 = TSHttpHdrMethodGet ( bufp4 , hdr_loc4 , & length2 ) ;
 if ( ( length1 != length2 ) || ( strncmp ( method1 , method2 , length1 ) != 0 ) ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_FAIL , "Method mismatch in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 if ( ( TSHttpHdrUrlGet ( bufp1 , hdr_loc1 , & url_loc1 ) != TS_SUCCESS ) || ( TSHttpHdrUrlGet ( bufp4 , hdr_loc4 , & url_loc2 ) != TS_SUCCESS ) ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_FAIL , "TSHttpVersionGet returns TS_ERROR" ) ;
 }
 else {
 const char * scheme1 ;
 const char * scheme2 ;
 const char * host1 ;
 const char * host2 ;
 int port1 ;
 int port2 ;
 const char * path1 ;
 const char * path2 ;
 scheme1 = TSUrlSchemeGet ( bufp1 , url_loc1 , & length1 ) ;
 scheme2 = TSUrlSchemeGet ( bufp4 , url_loc2 , & length2 ) ;
 if ( ( length1 != length2 ) || ( strncmp ( scheme1 , scheme2 , length1 ) != 0 ) ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_FAIL , "Url Scheme has different values in both headers" ) ;
 flag = false ;
 }
 if ( flag == true ) {
 host1 = TSUrlHostGet ( bufp1 , url_loc1 , & length1 ) ;
 host2 = TSUrlHostGet ( bufp4 , url_loc2 , & length2 ) ;
 if ( ( length1 != length2 ) || ( strncmp ( host1 , host2 , length1 ) != 0 ) ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_FAIL , "Url Host has different values in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 port1 = TSUrlPortGet ( bufp1 , url_loc1 ) ;
 port2 = TSUrlPortGet ( bufp4 , url_loc2 ) ;
 if ( port1 != port2 ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_FAIL , "Url Port has different values in both headers" ) ;
 flag = false ;
 }
 }
 if ( flag == true ) {
 path1 = TSUrlPathGet ( bufp1 , url_loc1 , & length1 ) ;
 path2 = TSUrlPathGet ( bufp4 , url_loc2 , & length2 ) ;
 if ( ( path1 != nullptr ) && ( path2 != nullptr ) ) {
 if ( ( length1 != length2 ) || ( strncmp ( path1 , path2 , length1 ) != 0 ) ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Url Path has different values in both headers" ) ;
 flag = false ;
 }
 }
 else {
 if ( path1 != path2 ) {
 SDK_RPRINT ( test , "TSHttpHdrCopy" , "TestCase1" , TC_FAIL , "Url Host has different values in both headers" ) ;
 flag = false ;
 }
 }
 if ( ( TSHandleMLocRelease ( bufp1 , hdr_loc1 , url_loc1 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp4 , hdr_loc4 , url_loc2 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "" , TC_FAIL , "Unable to release Handle acquired by TSHttpHdrUrlGet" ) ;
 }
 }
 if ( flag == true ) {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Clone = true ;
 }
 }
 }
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrClone" , "All Test Cases" , TC_PASS , "Cannot run test as TSHttpHdrCreate has failed" ) ;
 }
 if ( test_passed_Http_Hdr_Create == true ) {
 actual_length = TSHttpHdrLengthGet ( bufp1 , hdr_loc1 ) ;
 TSIOBuffer iobuf = TSIOBufferCreate ( ) ;
 TSHttpHdrPrint ( bufp1 , hdr_loc1 , iobuf ) ;
 TSIOBufferReader iobufreader = TSIOBufferReaderAlloc ( iobuf ) ;
 expected_length = TSIOBufferReaderAvail ( iobufreader ) ;
 if ( actual_length == expected_length ) {
 SDK_RPRINT ( test , "TSHttpHdrLengthGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Length = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrLengthGet" , "TestCase1" , TC_FAIL , "Incorrect value returned." ) ;
 }
 if ( ( test_passed_Http_Hdr_Method == true ) && ( test_passed_Http_Hdr_Url == true ) && ( test_passed_Http_Hdr_Version == true ) && ( test_passed_Http_Hdr_Length == true ) && ( try_print_function == true ) ) {
 char * actual_iobuf = nullptr ;
 actual_iobuf = ( char * ) TSmalloc ( ( actual_length + 1 ) * sizeof ( char ) ) ;
 if ( actual_iobuf == nullptr ) {
 SDK_RPRINT ( test , "TSHttpHdrPrint" , "TestCase1" , TC_FAIL , "Unable to allocate memory" ) ;
 }
 else {
 TSIOBufferBlock iobufblock ;
 int64_t bytes_read ;
 memset ( actual_iobuf , 0 , ( actual_length + 1 ) * sizeof ( char ) ) ;
 bytes_read = 0 ;
 iobufblock = TSIOBufferReaderStart ( iobufreader ) ;
 while ( iobufblock != nullptr ) {
 const char * block_start ;
 int64_t block_size ;
 block_start = TSIOBufferBlockReadStart ( iobufblock , iobufreader , & block_size ) ;
 if ( block_size <= 0 ) {
 break ;
 }
 memcpy ( actual_iobuf + bytes_read , block_start , block_size ) ;
 bytes_read += block_size ;
 TSIOBufferReaderConsume ( iobufreader , block_size ) ;
 iobufblock = TSIOBufferReaderStart ( iobufreader ) ;
 }
 if ( strcmp ( actual_iobuf , expected_iobuf ) == 0 ) {
 SDK_RPRINT ( test , "TSHttpHdrPrint" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Print = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrPrint" , "TestCase1" , TC_FAIL , "Value's mismatch" ) ;
 }
 TSfree ( actual_iobuf ) ;
 TSIOBufferReaderFree ( iobufreader ) ;
 TSIOBufferDestroy ( iobuf ) ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrPrint" , "TestCase1" , TC_FAIL , "Unable to run test for TSHttpHdrPrint" ) ;
 }
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrLengthGet" , "All Test Cases" , TC_PASS , "Cannot run test as TSHttpHdrCreate has failed" ) ;
 }
 if ( test_passed_Http_Hdr_Create == true ) {
 TSHttpHdrDestroy ( bufp1 , hdr_loc1 ) ;
 TSHttpHdrDestroy ( bufp2 , hdr_loc2 ) ;
 TSHttpHdrDestroy ( bufp3 , hdr_loc3 ) ;
 TSHttpHdrDestroy ( bufp4 , hdr_loc4 ) ;
 if ( ( TSHandleMLocRelease ( bufp1 , TS_NULL_MLOC , hdr_loc1 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp2 , TS_NULL_MLOC , hdr_loc2 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp3 , TS_NULL_MLOC , hdr_loc3 ) == TS_ERROR ) || ( TSHandleMLocRelease ( bufp4 , TS_NULL_MLOC , hdr_loc4 ) == TS_ERROR ) ) {
 SDK_RPRINT ( test , "TSHandleMLocRelease" , "TestCase1|2|3|4" , TC_FAIL , "Unable to release the handle to headers" ) ;
 }
 SDK_RPRINT ( test , "TSHttpHdrDestroy" , "TestCase1&2&3&4" , TC_PASS , "ok" ) ;
 test_passed_Http_Hdr_Destroy = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrDestroy" , "All Test Cases" , TC_FAIL , "Cannot run test as header was not created" ) ;
 }
 if ( bufp1 ) {
 if ( TSMBufferDestroy ( bufp1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMBufferDestroy" , "TestCase1" , TC_FAIL , "Unable to destroy MBuffer" ) ;
 }
 }
 if ( bufp2 ) {
 if ( TSMBufferDestroy ( bufp2 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMBufferDestroy" , "TestCase2" , TC_FAIL , "Unable to destroy MBuffer" ) ;
 }
 }
 if ( bufp3 ) {
 if ( TSMBufferDestroy ( bufp3 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMBufferDestroy" , "TestCase3" , TC_FAIL , "Unable to destroy MBuffer" ) ;
 }
 }
 if ( bufp4 ) {
 if ( TSMBufferDestroy ( bufp4 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSMBufferDestroy" , "TestCase4" , TC_FAIL , "Unable to destroy MBuffer" ) ;
 }
 }
 if ( ( test_passed_Http_Hdr_Create == true ) && ( test_passed_Http_Hdr_Type == true ) && ( test_passed_Http_Hdr_Method == true ) && ( test_passed_Http_Hdr_Url == true ) && ( test_passed_Http_Hdr_Status == true ) && ( test_passed_Http_Hdr_Reason == true ) && ( test_passed_Http_Hdr_Reason_Lookup == true ) && ( test_passed_Http_Hdr_Version == true ) && ( test_passed_Http_Hdr_Copy == true ) && ( test_passed_Http_Hdr_Clone == true ) && ( test_passed_Http_Hdr_Length == true ) && ( test_passed_Http_Hdr_Print == true ) && ( test_passed_Http_Hdr_Destroy == true ) ) {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 else {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 return ;
 }