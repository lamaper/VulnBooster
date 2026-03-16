IN_PROC_BROWSER_TEST_F ( CrossOriginXHR , AllURLs ) {
 ASSERT_TRUE ( RunExtensionTest ( "cross_origin_xhr/all_urls" ) ) << message_ ;
 }