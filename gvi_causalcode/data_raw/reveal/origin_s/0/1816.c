IN_PROC_BROWSER_TEST_F ( CrossOriginXHR , ContentScript ) {
 ASSERT_TRUE ( StartFTPServer ( base : : FilePath ( kFtpDocRoot ) ) ) ;
 ASSERT_TRUE ( RunExtensionTest ( "cross_origin_xhr/content_script" ) ) << message_ ;
 }