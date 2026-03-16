IN_PROC_BROWSER_TEST_F ( DownloadExtensionTest , DownloadExtensionTest_SetShelfEnabled ) {
 LoadExtension ( "downloads_split" ) ;
 EXPECT_TRUE ( RunFunction ( new DownloadsSetShelfEnabledFunction ( ) , "[false]" ) ) ;
 EXPECT_FALSE ( DownloadCoreServiceFactory : : GetForBrowserContext ( browser ( ) -> profile ( ) ) -> IsShelfEnabled ( ) ) ;
 EXPECT_TRUE ( RunFunction ( new DownloadsSetShelfEnabledFunction ( ) , "[true]" ) ) ;
 EXPECT_TRUE ( DownloadCoreServiceFactory : : GetForBrowserContext ( browser ( ) -> profile ( ) ) -> IsShelfEnabled ( ) ) ;
 }