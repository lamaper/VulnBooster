REGRESSION_TEST ( SDK_API_TSIOBufferCreate ) ( RegressionTest * test , int , int * pstatus ) {
 bool test_passed = false ;
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 int64_t watermark = 1000 ;
 TSIOBuffer bufp = TSIOBufferCreate ( ) ;
 TSIOBufferWaterMarkSet ( bufp , watermark ) ;
 watermark = TSIOBufferWaterMarkGet ( bufp ) ;
 if ( watermark == 1000 ) {
 SDK_RPRINT ( test , "TSIOBufferCreate" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSIOBufferWaterMarkGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSIOBufferWaterMarkSet" , "TestCase1" , TC_PASS , "ok" ) ;
 test_passed = true ;
 }
 else {
 SDK_RPRINT ( test , "TSIOBufferCreate" , "TestCase1" , TC_FAIL , "watermark failed" ) ;
 SDK_RPRINT ( test , "TSIOBufferWaterMarkGet" , "TestCase1" , TC_FAIL , "watermark failed" ) ;
 SDK_RPRINT ( test , "TSIOBufferWaterMarkSet" , "TestCase1" , TC_FAIL , "watermark failed" ) ;
 }
 TSIOBufferDestroy ( bufp ) ;
 * pstatus = ( ( test_passed == true ) ? REGRESSION_TEST_PASSED : REGRESSION_TEST_FAILED ) ;
 return ;
 }