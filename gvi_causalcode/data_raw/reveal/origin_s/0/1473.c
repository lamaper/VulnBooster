REGRESSION_TEST ( SDK_API_TSIOBufferCopy ) ( RegressionTest * test , int , int * pstatus ) {
 bool test_passed = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 char input_buf [ ] = "This is the test for TSIOBufferCopy, TSIOBufferWrite, TSIOBufferReaderCopy" ;
 char output_buf [ 1024 ] ;
 TSIOBuffer bufp = TSIOBufferSizedCreate ( TS_IOBUFFER_SIZE_INDEX_4K ) ;
 TSIOBuffer bufp2 = TSIOBufferSizedCreate ( TS_IOBUFFER_SIZE_INDEX_4K ) ;
 TSIOBufferReader readerp = TSIOBufferReaderAlloc ( bufp ) ;
 TSIOBufferWrite ( bufp , input_buf , ( strlen ( input_buf ) + 1 ) ) ;
 TSIOBufferCopy ( bufp2 , readerp , ( strlen ( input_buf ) + 1 ) , 0 ) ;
 TSIOBufferReaderCopy ( readerp , output_buf , ( strlen ( input_buf ) + 1 ) ) ;
 if ( strcmp ( input_buf , output_buf ) == 0 ) {
 SDK_RPRINT ( test , "TSIOBufferWrite" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSIOBufferCopy" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSIOBufferReaderCopy" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed = true ;
 }
 else {
 SDK_RPRINT ( test , "TSIOBufferWrite" , "TestCase1" , TC_FAIL , "failed" ) ;
 SDK_RPRINT ( test , "TSIOBufferCopy" , "TestCase1" , TC_FAIL , "failed" ) ;
 SDK_RPRINT ( test , "TSIOBufferReaderCopy" , "TestCase1" , TC_FAIL , "failed" ) ;
 }
 * pstatus = ( ( test_passed == true ) ? REGRESSION_TEST_PASSED : REGRESSION_TEST_FAILED ) ;
 return ;
 }