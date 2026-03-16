IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerWithDownloadsBrowserTest , TestWithDownloadsFromDifferentProfiles ) {
 ProfileManager * profile_manager = g_browser_process -> profile_manager ( ) ;
 Profile * other_profile = nullptr ;
 {
 base : : FilePath path = profile_manager -> user_data_dir ( ) . AppendASCII ( "test_profile" ) ;
 base : : ScopedAllowBlockingForTesting allow_blocking ;
 if ( ! base : : PathExists ( path ) ) ASSERT_TRUE ( base : : CreateDirectory ( path ) ) ;
 other_profile = Profile : : CreateProfile ( path , NULL , Profile : : CREATE_MODE_SYNCHRONOUS ) ;
 }
 profile_manager -> RegisterTestingProfile ( other_profile , true , false ) ;
 Browser * other_profile_browser = CreateBrowser ( other_profile ) ;
 SetDownloadPathForProfile ( browser ( ) -> profile ( ) ) ;
 SetDownloadPathForProfile ( other_profile ) ;
 ASSERT_NO_FATAL_FAILURE ( CreateStalledDownload ( browser ( ) ) ) ;
 {
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 browser ( ) -> window ( ) -> Close ( ) ;
 close_observer . Wait ( ) ;
 }
 ui_test_utils : : BrowserAddedObserver new_browser_observer ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_CANCELS_CLOSE ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 Browser * opened_browser = new_browser_observer . WaitForSingleNewBrowser ( ) ;
 EXPECT_EQ ( GURL ( chrome : : kChromeUIDownloadsURL ) , opened_browser -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetURL ( ) ) ;
 EXPECT_EQ ( GURL ( "about:blank" ) , other_profile_browser -> tab_strip_model ( ) -> GetActiveWebContents ( ) -> GetURL ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 2 ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_ALLOWS_CLOSE ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 if ( browser_defaults : : kBrowserAliveWithNoWindows ) EXPECT_EQ ( 1 , DownloadCoreService : : NonMaliciousDownloadCountAllProfiles ( ) ) ;
 else EXPECT_EQ ( 0 , DownloadCoreService : : NonMaliciousDownloadCountAllProfiles ( ) ) ;
 }