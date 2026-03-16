REGRESSION_TEST ( SDK_API_TSSslServerContextCreate ) ( RegressionTest * test , int level , int * pstatus ) {
 TSSslContext ctx ;
 ctx = TSSslServerContextCreate ( ) ;
 * pstatus = ctx ? REGRESSION_TEST_PASSED : REGRESSION_TEST_FAILED ;
 TSSslContextDestroy ( ctx ) ;
 }