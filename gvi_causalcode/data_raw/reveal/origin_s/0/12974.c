IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , TestWithOffTheRecordDownloads ) {
 Profile * otr_profile = browser ( ) -> profile ( ) -> GetOffTheRecordProfile ( ) ;
 Browser * otr_browser = CreateBrowser ( otr_profile ) ;
 {
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 browser ( ) -> window ( ) -> Close ( ) ;
 close_observer . Wait ( ) ;
 }
 ASSERT_NO_FATAL_FAILURE ( CreateStalledDownload ( otr_browser ) ) ;
 content : : TestNavigationObserver navigation_observer ( otr_browser -> tab_strip_model ( ) -> GetActiveWebContents ( ) , 1 ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_CANCELS_CLOSE ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 navigation_observer . Wait ( ) ;
 EXPECT_EQ ( GURL ( chrome : : kChromeUIDownloadsURL ) , otr_browser -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetURL ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_ALLOWS_CLOSE ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 EXPECT_EQ ( 0 , DownloadCoreService : : NonMaliciousDownloadCountAllProfiles ( ) ) ;
 }