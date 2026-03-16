IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , TestHangInBeforeUnloadMultipleTabs ) {
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 0 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload_hang.html" ) ) ) ;
 AddBlankTabAndShow ( browsers_ [ 0 ] ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 0 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) ) ) ;
 AddBlankTabAndShow ( browsers_ [ 0 ] ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 0 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload_hang.html" ) ) ) ;
 PrepareForDialog ( browsers_ [ 0 ] -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) ) ;
 RepeatedNotificationObserver cancel_observer ( chrome : : NOTIFICATION_BROWSER_CLOSE_CANCELLED , 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( CancelClose ( ) ) ;
 cancel_observer . Wait ( ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_EQ ( 3 , browsers_ [ 0 ] -> tab_strip_model ( ) -> count ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }