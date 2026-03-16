REGRESSION_TEST ( SDK_API_TSHttpHdrParse ) ( RegressionTest * test , int , int * pstatus ) {
 const char * req = "GET http://www.example.com/ HTTP/1.1\r\nmimefield1:field1value1,field1value2\r\nmimefield2:field2value1,field2value2\r\n\r\n" ;
 const char * resp = "HTTP/1.1 200 OK\r\n1mimefield:1field1value,1field2value\r\n2mimefield:2field1value,2field2value\r\n\r\n" ;
 const char * start ;
 const char * end ;
 char * temp ;
 int retval ;
 TSMBuffer reqbufp ;
 TSMBuffer respbufp = ( TSMBuffer ) nullptr ;
 TSMLoc req_hdr_loc = ( TSMLoc ) nullptr ;
 TSMLoc resp_hdr_loc = ( TSMLoc ) nullptr ;
 TSHttpParser parser ;
 bool test_passed_parse_req = false ;
 bool test_passed_parse_resp = false ;
 bool test_passed_parser_clear = false ;
 bool test_passed_parser_destroy = false ;
 parser = TSHttpParserCreate ( ) ;
 SDK_RPRINT ( test , "TSHttpParserCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 reqbufp = TSMBufferCreate ( ) ;
 req_hdr_loc = TSHttpHdrCreate ( reqbufp ) ;
 start = req ;
 end = req + strlen ( req ) + 1 ;
 if ( ( retval = TSHttpHdrParseReq ( parser , reqbufp , req_hdr_loc , & start , end ) ) == TS_PARSE_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrParseReq" , "TestCase1" , TC_FAIL , "TSHttpHdrParseReq returns TS_PARSE_ERROR" ) ;
 }
 else {
 if ( retval == TS_PARSE_DONE ) {
 test_passed_parse_req = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrParseReq" , "TestCase1" , TC_FAIL , "Parsing Error" ) ;
 }
 }
 TSHttpParserClear ( parser ) ;
 SDK_RPRINT ( test , "TSHttpParserClear" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_parser_clear = true ;
 if ( test_passed_parser_clear == true ) {
 respbufp = TSMBufferCreate ( ) ;
 resp_hdr_loc = TSHttpHdrCreate ( respbufp ) ;
 start = resp ;
 end = resp + strlen ( resp ) + 1 ;
 if ( ( retval = TSHttpHdrParseResp ( parser , respbufp , resp_hdr_loc , & start , end ) ) == TS_PARSE_ERROR ) {
 SDK_RPRINT ( test , "TSHttpHdrParseResp" , "TestCase1" , TC_FAIL , "TSHttpHdrParseResp returns TS_PARSE_ERROR." ) ;
 }
 else {
 if ( retval == TS_PARSE_DONE ) {
 test_passed_parse_resp = true ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrParseResp" , "TestCase1" , TC_FAIL , "Parsing Error" ) ;
 }
 }
 }
 if ( test_passed_parse_req == true ) {
 temp = convert_http_hdr_to_string ( reqbufp , req_hdr_loc ) ;
 if ( strcmp ( req , temp ) == 0 ) {
 SDK_RPRINT ( test , "TSHttpHdrParseReq" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrParseReq" , "TestCase1" , TC_FAIL , "Incorrect parsing" ) ;
 test_passed_parse_req = false ;
 }
 TSfree ( temp ) ;
 }
 if ( test_passed_parse_resp == true ) {
 temp = convert_http_hdr_to_string ( respbufp , resp_hdr_loc ) ;
 if ( strcmp ( resp , temp ) == 0 ) {
 SDK_RPRINT ( test , "TSHttpHdrParseResp" , "TestCase1" , TC_PASS , "ok" ) ;
 }
 else {
 SDK_RPRINT ( test , "TSHttpHdrParseResp" , "TestCase1" , TC_FAIL , "Incorrect parsing" ) ;
 test_passed_parse_resp = false ;
 }
 TSfree ( temp ) ;
 }
 TSHttpParserDestroy ( parser ) ;
 SDK_RPRINT ( test , "TSHttpParserDestroy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_parser_destroy = true ;
 if ( ( test_passed_parse_req != true ) || ( test_passed_parse_resp != true ) || ( test_passed_parser_clear != true ) || ( test_passed_parser_destroy != true ) ) {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 else {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 TSMimeHdrDestroy ( reqbufp , req_hdr_loc ) ;
 TSHandleMLocRelease ( reqbufp , TS_NULL_MLOC , req_hdr_loc ) ;
 TSMBufferDestroy ( reqbufp ) ;
 if ( resp_hdr_loc ) {
 TSMimeHdrDestroy ( respbufp , resp_hdr_loc ) ;
 TSHandleMLocRelease ( respbufp , TS_NULL_MLOC , resp_hdr_loc ) ;
 }
 if ( respbufp ) {
 TSMBufferDestroy ( respbufp ) ;
 }
 return ;
 }