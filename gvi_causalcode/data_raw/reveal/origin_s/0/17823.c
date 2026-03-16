REGRESSION_TEST ( SDK_API_TSIOBufferReaderConsume ) ( RegressionTest * test , int , int * pstatus ) {
 bool test_passed = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 TSIOBuffer bufp = TSIOBufferSizedCreate ( TS_IOBUFFER_SIZE_INDEX_4K ) ;
 TSIOBufferReader readerp = TSIOBufferReaderAlloc ( bufp ) ;
 TSIOBufferProduce ( bufp , 10 ) ;
 TSIOBufferReaderConsume ( readerp , 10 ) ;
 int64_t reader_avail = TSIOBufferReaderAvail ( readerp ) ;
 if ( reader_avail == 0 ) {
 SDK_RPRINT ( test , "TSIOBufferReaderConsume" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed = true ;
 }
 else {
 SDK_RPRINT ( test , "TSIOBufferReaderConsume" , "TestCase1" , TC_FAIL , "failed" ) ;
 }
 * pstatus = ( ( test_passed == true ) ? REGRESSION_TEST_PASSED : REGRESSION_TEST_FAILED ) ;
 return ;
 }