IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerWithDownloadsBrowserTest , TestWithDownloads ) {
 SetDownloadPathForProfile ( browser ( ) -> profile ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( CreateStalledDownload ( browser ( ) ) ) ;
 content : : TestNavigationObserver navigation_observer ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , 1 ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_CANCELS_CLOSE ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 navigation_observer . Wait ( ) ;
 EXPECT_EQ ( GURL ( chrome : : kChromeUIDownloadsURL ) , browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetURL ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_ALLOWS_CLOSE ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 if ( browser_defaults : : kBrowserAliveWithNoWindows ) EXPECT_EQ ( 1 , DownloadCoreService : : NonMaliciousDownloadCountAllProfiles ( ) ) ;
 else EXPECT_EQ ( 0 , DownloadCoreService : : NonMaliciousDownloadCountAllProfiles ( ) ) ;
 }