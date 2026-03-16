REGRESSION_TEST ( SDK_API_TSIOBufferStart ) ( RegressionTest * test , int , int * pstatus ) {
 bool test_passed = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSIOBuffer bufp = TSIOBufferSizedCreate ( TS_IOBUFFER_SIZE_INDEX_4K ) ;
 TSIOBufferReader readerp = TSIOBufferReaderAlloc ( bufp ) ;
 if ( TSIOBufferStart ( bufp ) == TSIOBufferReaderStart ( readerp ) ) {
 SDK_RPRINT ( test , "TSIOBufferStart" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSIOBufferReaderStart" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed = true ;
 }
 else {
 SDK_RPRINT ( test , "TSIOBufferStart" , "TestCase1" , TC_FAIL , "failed" ) ;
 SDK_RPRINT ( test , "TSIOBufferReaderStart" , "TestCase1" , TC_FAIL , "failed" ) ;
 }
 * pstatus = ( ( test_passed == true ) ? REGRESSION_TEST_PASSED : REGRESSION_TEST_FAILED ) ;
 return ;
 }