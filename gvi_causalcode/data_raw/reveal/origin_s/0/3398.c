IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , TestWithOffTheRecordWindowAndRegularDownload ) {
 Profile * otr_profile = browser ( ) -> profile ( ) -> GetOffTheRecordProfile ( ) ;
 Browser * otr_browser = CreateBrowser ( otr_profile ) ;
 ASSERT_NO_FATAL_FAILURE ( CreateStalledDownload ( browser ( ) ) ) ;
 content : : TestNavigationObserver navigation_observer ( otr_browser -> tab_strip_model ( ) -> GetActiveWebContents ( ) , 1 ) ;
 ui_test_utils : : NavigateToURL ( otr_browser , GURL ( "about:blank" ) ) ;
 navigation_observer . Wait ( ) ;
 int num_downloads_blocking = 0 ;
 ASSERT_EQ ( Browser : : DOWNLOAD_CLOSE_OK , otr_browser -> OkToCloseWithInProgressDownloads ( & num_downloads_blocking ) ) ;
 ASSERT_EQ ( 0 , num_downloads_blocking ) ;
 {
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 otr_browser -> window ( ) -> Close ( ) ;
 close_observer . Wait ( ) ;
 }
 ASSERT_EQ ( Browser : : DOWNLOAD_CLOSE_BROWSER_SHUTDOWN , browser ( ) -> OkToCloseWithInProgressDownloads ( & num_downloads_blocking ) ) ;
 ASSERT_EQ ( 1 , num_downloads_blocking ) ;
 {
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 2 ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_ALLOWS_CLOSE ) ;
 close_observer . Wait ( ) ;
 }
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 if ( browser_defaults : : kBrowserAliveWithNoWindows ) EXPECT_EQ ( 1 , DownloadCoreService : : NonMaliciousDownloadCountAllProfiles ( ) ) ;
 else EXPECT_EQ ( 0 , DownloadCoreService : : NonMaliciousDownloadCountAllProfiles ( ) ) ;
 }