REGRESSION_TEST ( SDK_API_TSUrl ) ( RegressionTest * test , int , int * pstatus ) {
 TSMBuffer bufp1 = ( TSMBuffer ) nullptr ;
 TSMBuffer bufp2 = ( TSMBuffer ) nullptr ;
 TSMBuffer bufp3 = ( TSMBuffer ) nullptr ;
 TSMLoc url_loc1 ;
 TSMLoc url_loc2 ;
 TSMLoc url_loc3 ;
 const char * scheme = TS_URL_SCHEME_HTTP ;
 const char * scheme_get ;
 const char * user = "yyy" ;
 const char * user_get ;
 const char * password = "xxx" ;
 const char * password_get ;
 const char * host = "www.example.com" ;
 const char * host_get ;
 int port = 2021 ;
 char port_char [ 10 ] ;
 int port_get = 80 ;
 const char * path = "about/overview.html" ;
 const char * path_get ;
 const char * params = "abcdef" ;
 const char * params_get ;
 const char * query = "name=xxx" ;
 const char * query_get ;
 const char * fragment = "yyy" ;
 const char * fragment_get ;
 char * url_expected_string ;
 char * url_string_from_1 = ( char * ) nullptr ;
 char * url_string_from_2 = ( char * ) nullptr ;
 char * url_string_from_3 = ( char * ) nullptr ;
 char * url_string_from_print = ( char * ) nullptr ;
 int url_expected_length ;
 int url_length_from_1 ;
 int url_length_from_2 ;
 int type = 'a' ;
 int type_get ;
 int tmp_len ;
 bool test_passed_create = false ;
 bool test_passed_scheme = false ;
 bool test_passed_user = false ;
 bool test_passed_password = false ;
 bool test_passed_host = false ;
 bool test_passed_port = false ;
 bool test_passed_path = false ;
 bool test_passed_params = false ;
 bool test_passed_query = false ;
 bool test_passed_fragment = false ;
 bool test_passed_copy = false ;
 bool test_passed_clone = false ;
 bool test_passed_string1 = false ;
 bool test_passed_string2 = false ;
 bool test_passed_print = false ;
 bool test_passed_length1 = false ;
 bool test_passed_length2 = false ;
 bool test_passed_type = false ;
 int length ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 memset ( port_char , 0 , 10 ) ;
 snprintf ( port_char , sizeof ( port_char ) , "%d" , port ) ;
 url_expected_length = strlen ( scheme ) + strlen ( "://" ) + ( ( user == nullptr ) ? 0 : strlen ( user ) ) + ( ( password == nullptr ) ? ( ( user == nullptr ) ? 0 : strlen ( "@" ) ) : strlen ( ":" ) + strlen ( password ) + strlen ( "@" ) ) + strlen ( host ) + ( ( port == 80 ) ? 0 : strlen ( port_char ) + strlen ( ":" ) ) + strlen ( "/" ) + strlen ( path ) + ( ( params == nullptr ) ? 0 : strlen ( ";
" ) + strlen ( params ) ) + ( ( query == nullptr ) ? 0 : strlen ( "?" ) + strlen ( query ) ) + ( ( fragment == nullptr ) ? 0 : strlen ( "#" ) + strlen ( fragment ) ) ;
 size_t len = url_expected_length + 1 ;
 url_expected_string = ( char * ) TSmalloc ( len * sizeof ( char ) ) ;
 memset ( url_expected_string , 0 , url_expected_length + 1 ) ;
 snprintf ( url_expected_string , len , "%s://%s%s%s%s%s%s%s/%s%s%s%s%s%s%s" , scheme , ( ( user == nullptr ) ? "" : user ) , ( ( password == nullptr ) ? "" : ":" ) , ( ( password == nullptr ) ? "" : password ) , ( ( ( user == nullptr ) && ( password == nullptr ) ) ? "" : "@" ) , host , ( ( port == 80 ) ? "" : ":" ) , ( ( port == 80 ) ? "" : port_char ) , ( ( path == nullptr ) ? "" : path ) , ( ( params == nullptr ) ? "" : ";
" ) , ( ( params == nullptr ) ? "" : params ) , ( ( query == nullptr ) ? "" : "?" ) , ( ( query == nullptr ) ? "" : query ) , ( ( fragment == nullptr ) ? "" : "#" ) , ( ( fragment == nullptr ) ? "" : fragment ) ) ;
 bufp1 = TSMBufferCreate ( ) ;
 if ( TSUrlCreate ( bufp1 , & url_loc1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlCreate" , "TestCase1" , TC_FAIL , "unable to create URL within buffer." ) ;
 goto print_results ;
 }
 if ( TSUrlSchemeSet ( bufp1 , url_loc1 , scheme , - 1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlSchemeSet" , "TestCase1" , TC_FAIL , "TSUrlSchemeSet Returned TS_ERROR" ) ;
 }
 else {
 scheme_get = TSUrlSchemeGet ( bufp1 , url_loc1 , & length ) ;
 if ( strncmp ( scheme_get , scheme , length ) == 0 ) {
 SDK_RPRINT ( test , "TSUrlSchemeSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_scheme = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlSchemeSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 if ( TSUrlUserSet ( bufp1 , url_loc1 , user , - 1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlUserSet" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 user_get = TSUrlUserGet ( bufp1 , url_loc1 , & length ) ;
 if ( ( ( user_get == nullptr ) && ( user == nullptr ) ) || ( strncmp ( user_get , user , length ) == 0 ) ) {
 SDK_RPRINT ( test , "TSUrlUserSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_user = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlUserSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 if ( TSUrlPasswordSet ( bufp1 , url_loc1 , password , - 1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlPasswordSet" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 password_get = TSUrlPasswordGet ( bufp1 , url_loc1 , & length ) ;
 if ( ( ( password_get == nullptr ) && ( password == nullptr ) ) || ( strncmp ( password_get , password , length ) == 0 ) ) {
 SDK_RPRINT ( test , "TSUrlPasswordSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_password = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlPasswordSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 if ( TSUrlHostSet ( bufp1 , url_loc1 , host , - 1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlHostSet" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 host_get = TSUrlHostGet ( bufp1 , url_loc1 , & length ) ;
 if ( strncmp ( host_get , host , length ) == 0 ) {
 SDK_RPRINT ( test , "TSUrlHostSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_host = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlHostSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 if ( TSUrlPortSet ( bufp1 , url_loc1 , port ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlPortSet" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 port_get = TSUrlPortGet ( bufp1 , url_loc1 ) ;
 if ( port_get == port ) {
 SDK_RPRINT ( test , "TSUrlPortSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_port = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlPortSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 if ( TSUrlPathSet ( bufp1 , url_loc1 , path , - 1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlPathSet" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 path_get = TSUrlPathGet ( bufp1 , url_loc1 , & length ) ;
 if ( ( ( path == nullptr ) && ( path_get == nullptr ) ) || ( strncmp ( path , path_get , length ) == 0 ) ) {
 SDK_RPRINT ( test , "TSUrlPathSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_path = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlPathSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 if ( TSUrlHttpParamsSet ( bufp1 , url_loc1 , params , - 1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlHttpParamsSet" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 params_get = TSUrlHttpParamsGet ( bufp1 , url_loc1 , & length ) ;
 if ( ( ( params == nullptr ) && ( params_get == nullptr ) ) || ( strncmp ( params , params_get , length ) == 0 ) ) {
 SDK_RPRINT ( test , "TSUrlHttpParamsSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_params = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlHttpParamsSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 if ( TSUrlHttpQuerySet ( bufp1 , url_loc1 , query , - 1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlHttpQuerySet" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 query_get = TSUrlHttpQueryGet ( bufp1 , url_loc1 , & length ) ;
 if ( ( ( query == nullptr ) && ( query_get == nullptr ) ) || ( strncmp ( query , query_get , length ) == 0 ) ) {
 SDK_RPRINT ( test , "TSUrlHttpQuerySet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_query = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlHttpQuerySet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 if ( TSUrlHttpFragmentSet ( bufp1 , url_loc1 , fragment , - 1 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlHttpFragmentSet" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 fragment_get = TSUrlHttpFragmentGet ( bufp1 , url_loc1 , & length ) ;
 if ( ( ( fragment == nullptr ) && ( fragment_get == nullptr ) ) || ( strncmp ( fragment , fragment_get , length ) == 0 ) ) {
 SDK_RPRINT ( test , "TSUrlHttpFragmentSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_fragment = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlHttpFragmentSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 url_length_from_1 = TSUrlLengthGet ( bufp1 , url_loc1 ) ;
 if ( url_length_from_1 == url_expected_length ) {
 SDK_RPRINT ( test , "TSUrlLengthGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_length1 = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlLengthGet" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 url_string_from_1 = TSUrlStringGet ( bufp1 , url_loc1 , & tmp_len ) ;
 if ( strcmp ( url_string_from_1 , url_expected_string ) == 0 ) {
 SDK_RPRINT ( test , "TSUrlStringGet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_string1 = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlStringGet" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 bufp2 = TSMBufferCreate ( ) ;
 if ( TSUrlCreate ( bufp2 , & url_loc2 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlCreate" , "TestCase2" , TC_FAIL , "unable to create URL within buffer for TSUrlCopy." ) ;
 goto print_results ;
 }
 if ( TSUrlCopy ( bufp2 , url_loc2 , bufp1 , url_loc1 ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSUrlCopy" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 url_length_from_2 = TSUrlLengthGet ( bufp2 , url_loc2 ) ;
 if ( url_length_from_2 == url_expected_length ) {
 SDK_RPRINT ( test , "TSUrlLengthGet" , "TestCase2" , TC_PASS , "ok" ) ;
 test_passed_length2 = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlCopy" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 url_string_from_2 = TSUrlStringGet ( bufp2 , url_loc2 , & tmp_len ) ;
 if ( strcmp ( url_string_from_2 , url_expected_string ) == 0 ) {
 SDK_RPRINT ( test , "TSUrlStringGet" , "TestCase2" , TC_PASS , "ok" ) ;
 test_passed_string2 = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlStringGet" , "TestCase2" , TC_FAIL , "Values don't match" ) ;
 }
 if ( strcmp ( url_string_from_1 , url_string_from_2 ) == 0 ) {
 SDK_RPRINT ( test , "TSUrlCopy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_copy = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlCopy" , "TestCase1" , TC_FAIL , "Values Don't Match" ) ;
 }
 }
 bufp3 = TSMBufferCreate ( ) ;
 if ( TSUrlClone ( bufp3 , bufp1 , url_loc1 , & url_loc3 ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlClone" , "TestCase1" , TC_FAIL , "Returned TS_ERROR" ) ;
 }
 else {
 url_string_from_3 = TSUrlStringGet ( bufp3 , url_loc3 , & tmp_len ) ;
 if ( strcmp ( url_string_from_1 , url_string_from_3 ) == 0 ) {
 SDK_RPRINT ( test , "TSUrlClone" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_clone = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlClone" , "TestCase1" , TC_FAIL , "Values Don't Match" ) ;
 }
 }
 url_string_from_print = test_url_print ( bufp1 , url_loc1 ) ;
 if ( url_string_from_print == nullptr ) {
 SDK_RPRINT ( test , "TSUrlPrint" , "TestCase1" , TC_FAIL , "TSUrlPrint doesn't return TS_SUCCESS" ) ;
 }
 else {
 if ( strcmp ( url_string_from_print , url_expected_string ) == 0 ) {
 SDK_RPRINT ( test , "TSUrlPrint" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_print = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlPrint" , "TestCase1" , TC_FAIL , "TSUrlPrint doesn't return TS_SUCCESS" ) ;
 }
 TSfree ( url_string_from_print ) ;
 }
 if ( TSUrlFtpTypeSet ( bufp1 , url_loc1 , type ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlFtpTypeSet" , "TestCase1" , TC_FAIL , "TSUrlFtpTypeSet Returned TS_ERROR" ) ;
 }
 else {
 type_get = TSUrlFtpTypeGet ( bufp1 , url_loc1 ) ;
 if ( type_get == type ) {
 SDK_RPRINT ( test , "TSUrlFtpTypeSet&Get" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_type = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlFtpTypeSet&Get" , "TestCase1" , TC_FAIL , "Values don't match" ) ;
 }
 }
 SDK_RPRINT ( test , "TSUrlCreate" , "TestCase1&2" , TC_PASS , "ok" ) ;
 TSHandleMLocRelease ( bufp1 , TS_NULL_MLOC , url_loc1 ) ;
 TSHandleMLocRelease ( bufp2 , TS_NULL_MLOC , url_loc2 ) ;
 TSHandleMLocRelease ( bufp3 , TS_NULL_MLOC , url_loc3 ) ;
 test_passed_create = true ;
 print_results : TSfree ( url_expected_string ) ;
 if ( url_string_from_1 != nullptr ) {
 TSfree ( url_string_from_1 ) ;
 }
 if ( url_string_from_2 != nullptr ) {
 TSfree ( url_string_from_2 ) ;
 }
 if ( url_string_from_3 != nullptr ) {
 TSfree ( url_string_from_3 ) ;
 }
 if ( bufp1 != nullptr ) {
 TSMBufferDestroy ( bufp1 ) ;
 }
 if ( bufp2 != nullptr ) {
 TSMBufferDestroy ( bufp2 ) ;
 }
 if ( bufp3 != nullptr ) {
 TSMBufferDestroy ( bufp3 ) ;
 }
 if ( ( test_passed_create == false ) || ( test_passed_scheme == false ) || ( test_passed_user == false ) || ( test_passed_password == false ) || ( test_passed_host == false ) || ( test_passed_port == false ) || ( test_passed_path == false ) || ( test_passed_params == false ) || ( test_passed_query == false ) || ( test_passed_fragment == false ) || ( test_passed_copy == false ) || ( test_passed_clone == false ) || ( test_passed_string1 == false ) || ( test_passed_string2 == false ) || ( test_passed_print == false ) || ( test_passed_length1 == false ) || ( test_passed_length2 == false ) || ( test_passed_type == false ) ) {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 else {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 }