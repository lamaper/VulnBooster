REGRESSION_TEST ( SDK_API_TSUrlParse ) ( RegressionTest * test , int , int * pstatus ) {
 static const char * const urls [ ] = {
 "file:///test.dat;
ab?abc=def#abc" , "http://www.example.com/" , "http://abc:def@www.example.com/" , "http://www.example.com:3426/" , "http://abc:def@www.example.com:3426/" , "http://www.example.com/homepage.cgi" , "http://www.example.com/homepage.cgi;
ab?abc=def#abc" , "http://abc:def@www.example.com:3426/homepage.cgi;
ab?abc=def#abc" , "https://abc:def@www.example.com:3426/homepage.cgi;
ab?abc=def#abc" , "ftp://abc:def@www.example.com:3426/homepage.cgi;
ab?abc=def#abc" , "file:///c:/test.dat;
ab?abc=def#abc" , "file:///test.dat;
ab?abc=def#abc" , "foo://bar.com/baz/" , "http://a.b.com/xx.jpg?newpath=http://b.c.com" }
 ;
 static int const num_urls = sizeof ( urls ) / sizeof ( urls [ 0 ] ) ;
 bool test_passed [ num_urls ] = {
 false }
 ;
 const char * start ;
 const char * end ;
 char * temp ;
 int retval ;
 TSMBuffer bufp ;
 TSMLoc url_loc = ( TSMLoc ) nullptr ;
 int length ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 int idx ;
 for ( idx = 0 ;
 idx < num_urls ;
 idx ++ ) {
 const char * url = urls [ idx ] ;
 bufp = TSMBufferCreate ( ) ;
 if ( TSUrlCreate ( bufp , & url_loc ) != TS_SUCCESS ) {
 SDK_RPRINT ( test , "TSUrlParse" , url , TC_FAIL , "Cannot create Url for parsing the url" ) ;
 if ( TSMBufferDestroy ( bufp ) == TS_ERROR ) {
 SDK_RPRINT ( test , "TSUrlParse" , url , TC_FAIL , "Error in Destroying MBuffer" ) ;
 }
 }
 else {
 start = url ;
 end = url + strlen ( url ) ;
 if ( ( retval = TSUrlParse ( bufp , url_loc , & start , end ) ) == TS_PARSE_ERROR ) {
 SDK_RPRINT ( test , "TSUrlParse" , url , TC_FAIL , "TSUrlParse returns TS_PARSE_ERROR" ) ;
 }
 else {
 if ( retval == TS_PARSE_DONE ) {
 temp = TSUrlStringGet ( bufp , url_loc , & length ) ;
 if ( strncmp ( url , temp , length ) == 0 ) {
 SDK_RPRINT ( test , "TSUrlParse" , url , TC_PASS , "ok" ) ;
 test_passed [ idx ] = true ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlParse" , url , TC_FAIL , "Value's Mismatch" ) ;
 }
 TSfree ( temp ) ;
 }
 else {
 SDK_RPRINT ( test , "TSUrlParse" , url , TC_FAIL , "Parsing Error" ) ;
 }
 }
 }
 TSHandleMLocRelease ( bufp , TS_NULL_MLOC , url_loc ) ;
 TSMBufferDestroy ( bufp ) ;
 }
 for ( idx = 0 ;
 idx < num_urls ;
 idx ++ ) {
 if ( test_passed [ idx ] != true ) {
 * pstatus = REGRESSION_TEST_FAILED ;
 break ;
 }
 }
 if ( idx >= num_urls ) {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 return ;
 }