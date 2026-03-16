IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerWithDownloadsBrowserTest , DISABLED_TestBeforeUnloadAndDownloads ) {
 SetDownloadPathForProfile ( browser ( ) -> profile ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( CreateStalledDownload ( browser ( ) ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) ) ) ;
 PrepareForDialog ( browser ( ) ) ;
 content : : WindowedNotificationObserver cancel_observer ( chrome : : NOTIFICATION_BROWSER_CLOSE_CANCELLED , content : : NotificationService : : AllSources ( ) ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_CANCELS_CLOSE ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 cancel_observer . Wait ( ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 TestBrowserCloseManager : : AttemptClose ( TestBrowserCloseManager : : USER_CHOICE_USER_ALLOWS_CLOSE ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }