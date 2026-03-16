IN_PROC_BROWSER_TEST_F ( CrossOriginXHR , BackgroundPage ) {
 ASSERT_TRUE ( StartFTPServer ( base : : FilePath ( kFtpDocRoot ) ) ) ;
 ASSERT_TRUE ( RunExtensionTest ( "cross_origin_xhr/background_page" ) ) << message_ ;
 }