IN_PROC_BROWSER_TEST_F ( CrossOriginXHR , NoFileAccess ) {
 ASSERT_TRUE ( RunExtensionTestNoFileAccess ( "cross_origin_xhro_file_access" ) ) << message_ ;
 }