REGRESSION_TEST ( SDK_API_TSIOBufferBlockReadAvail ) ( RegressionTest * test , int , int * pstatus ) {
 bool test_passed_1 = false ;
 bool test_passed_2 = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 int i = 10000 ;
 TSIOBuffer bufp = TSIOBufferCreate ( ) ;
 TSIOBufferWrite ( bufp , ( char * ) & i , sizeof ( int ) ) ;
 TSIOBufferReader readerp = TSIOBufferReaderAlloc ( bufp ) ;
 int64_t avail_write , avail_read ;
 TSIOBufferBlock blockp = TSIOBufferStart ( bufp ) ;
 if ( ( TSIOBufferBlockWriteStart ( blockp , & avail_write ) - TSIOBufferBlockReadStart ( blockp , readerp , & avail_read ) ) == sizeof ( int ) ) {
 SDK_RPRINT ( test , "TSIOBufferBlockReadStart" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSIOBufferBlockWriteStart" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_1 = true ;
 }
 else {
 SDK_RPRINT ( test , "TSIOBufferBlockReadStart" , "TestCase1" , TC_FAIL , "failed" ) ;
 SDK_RPRINT ( test , "TSIOBufferBlockWriteStart" , "TestCase1" , TC_FAIL , "failed" ) ;
 }
 if ( ( TSIOBufferBlockReadAvail ( blockp , readerp ) + TSIOBufferBlockWriteAvail ( blockp ) ) == 4096 ) {
 SDK_RPRINT ( test , "TSIOBufferBlockReadAvail" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSIOBufferBlockWriteAvail" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed_2 = true ;
 }
 else {
 SDK_RPRINT ( test , "TSIOBufferBlockReadAvail" , "TestCase1" , TC_FAIL , "failed" ) ;
 SDK_RPRINT ( test , "TSIOBufferBlockWriteAvail" , "TestCase1" , TC_FAIL , "failed" ) ;
 }
 if ( test_passed_1 && test_passed_2 ) {
 * pstatus = REGRESSION_TEST_PASSED ;
 }
 else {
 * pstatus = REGRESSION_TEST_FAILED ;
 }
 return ;
 }