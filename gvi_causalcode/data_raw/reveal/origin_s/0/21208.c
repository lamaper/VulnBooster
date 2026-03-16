REGRESSION_TEST ( SDK_API_ENCODING ) ( RegressionTest * test , int , int * pstatus ) {
 const char * url = "http://www.example.com/foo?fie= \"#%<>[]\\^`{
}
~&bar={
test}
&fum=Apache Traffic Server" ;
 const char * url_encoded = "http://www.example.com/foo?fie=%20%22%23%25%3C%3E%5B%5D%5C%5E%60%7B%7D%7E&bar=%7Btest%7D&fum=Apache%20Traffic%20Server" ;
 const char * url_base64 = "aHR0cDovL3d3dy5leGFtcGxlLmNvbS9mb28/ZmllPSAiIyU8PltdXF5ge31+JmJhcj17dGVzdH0mZnVtPUFwYWNoZSBUcmFmZmljIFNlcnZlcg==" ;
 const char * url2 = "http://www.example.com/" ;
 const char * url3 = "https://www.thisisoneexampleofastringoflengtheightyasciilowercasecharacters.com/" ;
 char buf [ 1024 ] ;
 size_t length ;
 bool success = true ;
 if ( TS_SUCCESS != TSStringPercentEncode ( url , strlen ( url ) , buf , sizeof ( buf ) , & length , nullptr ) ) {
 SDK_RPRINT ( test , "TSStringPercentEncode" , "TestCase1" , TC_FAIL , "Failed on %s" , url ) ;
 success = false ;
 }
 else {
 if ( strcmp ( buf , url_encoded ) ) {
 SDK_RPRINT ( test , "TSStringPercentEncode" , "TestCase1" , TC_FAIL , "Failed on %s != %s" , buf , url_encoded ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSStringPercentEncode" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
 if ( TS_SUCCESS != TSStringPercentEncode ( url2 , strlen ( url2 ) , buf , sizeof ( buf ) , & length , nullptr ) ) {
 SDK_RPRINT ( test , "TSStringPercentEncode" , "TestCase2" , TC_FAIL , "Failed on %s" , url2 ) ;
 success = false ;
 }
 else {
 if ( strcmp ( buf , url2 ) ) {
 SDK_RPRINT ( test , "TSStringPercentEncode" , "TestCase2" , TC_FAIL , "Failed on %s != %s" , buf , url2 ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSStringPercentEncode" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 }
 if ( TS_SUCCESS != TSStringPercentDecode ( url_encoded , strlen ( url_encoded ) , buf , sizeof ( buf ) , & length ) ) {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase1" , TC_FAIL , "Failed on %s" , url_encoded ) ;
 success = false ;
 }
 else {
 if ( length != strlen ( url ) || strcmp ( buf , url ) ) {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase1" , TC_FAIL , "Failed on %s != %s" , buf , url ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
 if ( TS_SUCCESS != TSStringPercentDecode ( url2 , strlen ( url2 ) , buf , sizeof ( buf ) , & length ) ) {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase2" , TC_FAIL , "Failed on %s" , url2 ) ;
 success = false ;
 }
 else {
 if ( length != strlen ( url2 ) || strcmp ( buf , url2 ) ) {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase2" , TC_FAIL , "Failed on %s != %s" , buf , url2 ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase2" , TC_PASS , "ok" ) ;
 }
 }
 const size_t buf_len = strlen ( url3 ) + 1 ;
 strncpy ( buf , url3 , buf_len - 1 ) ;
 const char canary = 0xFF ;
 buf [ buf_len - 1 ] = canary ;
 const char * url3_clipped = "https://www.thisisoneexampleofastringoflengtheightyasciilowercasecharacters.com" ;
 if ( TS_SUCCESS != TSStringPercentDecode ( buf , buf_len - 1 , buf , buf_len - 1 , & length ) ) {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase3" , TC_FAIL , "Failed on %s" , url3 ) ;
 success = false ;
 }
 else {
 if ( memcmp ( buf + buf_len - 1 , & canary , 1 ) ) {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase3" , TC_FAIL , "Failed on %s overwrites buffer" , url3 ) ;
 success = false ;
 }
 else if ( length != strlen ( url3_clipped ) || strcmp ( buf , url3_clipped ) ) {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase3" , TC_FAIL , "Failed on %s != %s" , buf , url3_clipped ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSStringPercentDecode" , "TestCase3" , TC_PASS , "ok" ) ;
 }
 }
 if ( TS_SUCCESS != TSBase64Encode ( url , strlen ( url ) , buf , sizeof ( buf ) , & length ) ) {
 SDK_RPRINT ( test , "TSBase64Encode" , "TestCase1" , TC_FAIL , "Failed on %s" , url ) ;
 success = false ;
 }
 else {
 if ( length != strlen ( url_base64 ) || strcmp ( buf , url_base64 ) ) {
 SDK_RPRINT ( test , "TSBase64Encode" , "TestCase1" , TC_FAIL , "Failed on %s != %s" , buf , url_base64 ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSBase64Encode" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
 if ( TS_SUCCESS != TSBase64Decode ( url_base64 , strlen ( url_base64 ) , ( unsigned char * ) buf , sizeof ( buf ) , & length ) ) {
 SDK_RPRINT ( test , "TSBase64Decode" , "TestCase1" , TC_FAIL , "Failed on %s" , url_base64 ) ;
 success = false ;
 }
 else {
 if ( length != strlen ( url ) || strcmp ( buf , url ) ) {
 SDK_RPRINT ( test , "TSBase64Decode" , "TestCase1" , TC_FAIL , "Failed on %s != %s" , buf , url ) ;
 success = false ;
 }
 else {
 SDK_RPRINT ( test , "TSBase64Decode" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 }
 * pstatus = success ? REGRESSION_TEST_PASSED : REGRESSION_TEST_FAILED ;
 return ;
 }