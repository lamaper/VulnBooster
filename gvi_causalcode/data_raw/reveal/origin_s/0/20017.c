IN_PROC_BROWSER_TEST_F ( CrossOriginXHR , FileAccessNoHosts ) {
 ASSERT_TRUE ( RunExtensionTest ( "cross_origin_xhr/file_access_no_hosts" ) ) << message_ ;
 }