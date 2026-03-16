REGRESSION_TEST ( SDK_API_TSIOBufferBlockNext ) ( RegressionTest * test , int , int * pstatus ) {
 bool test_passed = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 int i = 10000 ;
 TSIOBuffer bufp = TSIOBufferCreate ( ) ;
 TSIOBufferWrite ( bufp , ( char * ) & i , sizeof ( int ) ) ;
 TSIOBufferReader readerp = TSIOBufferReaderAlloc ( bufp ) ;
 TSIOBufferBlock blockp = TSIOBufferReaderStart ( readerp ) ;
 if ( TSIOBufferBlockNext ( blockp ) == nullptr ) {
 SDK_RPRINT ( test , "TSIOBufferBlockNext" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed = true ;
 }
 else {
 SDK_RPRINT ( test , "TSIOBufferBlockNext" , "TestCase1" , TC_FAIL , "fail" ) ;
 }
 if ( test_passed ) {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 else {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 return ;
 }