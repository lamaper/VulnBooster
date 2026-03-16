IN_PROC_BROWSER_TEST_F ( CrossOriginXHR , FileAccess ) {
 ASSERT_TRUE ( RunExtensionTest ( "cross_origin_xhr/file_access" ) ) << message_ ;
 }