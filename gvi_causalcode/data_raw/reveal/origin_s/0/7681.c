IN_PROC_BROWSER_TEST_F ( CrossOriginXHR , FileAccessAllURLs ) {
 ASSERT_TRUE ( RunExtensionTest ( "cross_origin_xhr/file_access_all_urls" ) ) << message_ ;
 }