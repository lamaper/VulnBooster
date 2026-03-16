REGRESSION_TEST ( SDK_API_TSConfig ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 ConfigData * config = ( ConfigData * ) TSmalloc ( sizeof ( ConfigData ) ) ;
 config -> a = "unit" ;
 config -> b = "test" ;
 my_config_id = TSConfigSet ( 0 , config , config_destroy_func ) ;
 TSConfig test_config = nullptr ;
 test_config = TSConfigGet ( my_config_id ) ;
 if ( ! test_config ) {
 SDK_RPRINT ( test , "TSConfigSet" , "TestCase1" , TC_FAIL , "can't correctly set global config structure" ) ;
 SDK_RPRINT ( test , "TSConfigGet" , "TestCase1" , TC_FAIL , "can't correctly get global config structure" ) ;
 TSConfigRelease ( my_config_id , reinterpret_cast < TSConfig > ( config ) ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 if ( TSConfigDataGet ( test_config ) != config ) {
 SDK_RPRINT ( test , "TSConfigDataGet" , "TestCase1" , TC_FAIL , "failed to get config data" ) ;
 TSConfigRelease ( my_config_id , reinterpret_cast < TSConfig > ( config ) ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 SDK_RPRINT ( test , "TSConfigGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSConfigSet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSConfigDataGet" , "TestCase1" , TC_PASS , "ok" ) ;
 TSConfigRelease ( my_config_id , reinterpret_cast < TSConfig > ( config ) ) ;
 * pstatus = REGRESSION_TEST_PASSED ;
 return ;
 }