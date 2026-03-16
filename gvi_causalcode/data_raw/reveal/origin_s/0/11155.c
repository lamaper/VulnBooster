IN_PROC_BROWSER_TEST_F ( CrossOriginXHR , NoFileAccessAllURLs ) {
 ASSERT_TRUE ( RunExtensionTestNoFileAccess ( "cross_origin_xhro_file_access_all_urls" ) ) << message_ ;
 }