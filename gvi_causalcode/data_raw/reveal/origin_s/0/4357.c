REGRESSION_TEST ( SDK_API_TSPluginDirGet ) ( RegressionTest * test , int , int * pstatus ) {
 * pstatus = REGRESSION_TEST_INPROGRESS ;
 const char * plugin_dir = TSPluginDirGet ( ) ;
 const char * install_dir = TSInstallDirGet ( ) ;
 const char * runtime_dir = TSRuntimeDirGet ( ) ;
 if ( ! plugin_dir ) {
 SDK_RPRINT ( test , "TSPluginDirGet" , "TestCase1" , TC_FAIL , "can't get plugin dir" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 if ( ! install_dir ) {
 SDK_RPRINT ( test , "TSInstallDirGet" , "TestCase1" , TC_FAIL , "can't get installation dir" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 if ( ! runtime_dir ) {
 SDK_RPRINT ( test , "TSRuntimeDirGet" , "TestCase1" , TC_FAIL , "can't get runtime dir" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 if ( strstr ( plugin_dir , TS_BUILD_LIBEXECDIR ) == nullptr ) {
 SDK_RPRINT ( test , "TSPluginDirGet" , "TestCase2" , TC_FAIL , "plugin dir(%s) is incorrect, expected (%s) in path." , plugin_dir , TS_BUILD_LIBEXECDIR ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 if ( strstr ( plugin_dir , install_dir ) == nullptr ) {
 SDK_RPRINT ( test , "TSInstallDirGet" , "TestCase2" , TC_FAIL , "install dir is incorrect" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 if ( strstr ( runtime_dir , TS_BUILD_RUNTIMEDIR ) == nullptr ) {
 SDK_RPRINT ( test , "TSRuntimeDirGet" , "TestCase2" , TC_FAIL , "runtime dir is incorrect" ) ;
 * pstatus = REGRESSION_TEST_FAILED ;
 return ;
 }
 SDK_RPRINT ( test , "TSPluginDirGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSInstallDirGet" , "TestCase1" , TC_PASS , "ok" ) ;
 SDK_RPRINT ( test , "TSRuntimeDirGet" , "TestCase1" , TC_PASS , "ok" ) ;
 * pstatus = REGRESSION_TEST_PASSED ;
 return ;
 }