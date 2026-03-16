REGRESSION_TEST ( SDK_API_TSContDataGet ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 SDK_ContData_test = test ;
 SDK_ContData_pstatus = pstatus ;
 TSCont contp = TSContCreate ( cont_data_handler , TSMutexCreate ( ) ) ;
 MyData * my_data = ( MyData * ) TSmalloc ( sizeof ( MyData ) ) ;
 my_data -> data1 = 1 ;
 my_data -> data2 = 2 ;
 TSContDataSet ( contp , ( void * ) my_data ) ;
 TSContSchedule ( contp , 0 , TS_THREAD_POOL_DEFAULT ) ;
 }