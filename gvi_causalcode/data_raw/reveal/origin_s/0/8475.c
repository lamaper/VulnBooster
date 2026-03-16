IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , TestShutdownMoreThanOnce ) {
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) ) ) ;
 PrepareForDialog ( browser ( ) ) ;
 RepeatedNotificationObserver cancel_observer ( chrome : : NOTIFICATION_BROWSER_CLOSE_CANCELLED , 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( CancelClose ( ) ) ;
 cancel_observer . Wait ( ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_EQ ( 1 , browser ( ) -> tab_strip_model ( ) -> count ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }