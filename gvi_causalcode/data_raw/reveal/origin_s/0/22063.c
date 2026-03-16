IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , TestHangInBeforeUnloadMultipleWindows ) {
 browsers_ . push_back ( CreateBrowser ( browser ( ) -> profile ( ) ) ) ;
 browsers_ . push_back ( CreateBrowser ( browser ( ) -> profile ( ) ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 0 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload_hang.html" ) ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 1 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 2 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload_hang.html" ) ) ) ;
 PrepareForDialog ( browsers_ [ 1 ] ) ;
 RepeatedNotificationObserver cancel_observer ( chrome : : NOTIFICATION_BROWSER_CLOSE_CANCELLED , 2 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( CancelClose ( ) ) ;
 cancel_observer . Wait ( ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_EQ ( 1 , browsers_ [ 0 ] -> tab_strip_model ( ) -> count ( ) ) ;
 EXPECT_EQ ( 1 , browsers_ [ 1 ] -> tab_strip_model ( ) -> count ( ) ) ;
 EXPECT_EQ ( 1 , browsers_ [ 2 ] -> tab_strip_model ( ) -> count ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 3 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }