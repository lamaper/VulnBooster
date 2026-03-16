IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , MAYBE_TestAddWindowDuringShutdown ) {
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 0 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) ) ) ;
 PrepareForDialog ( browsers_ [ 0 ] ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 2 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 browsers_ . push_back ( CreateBrowser ( browser ( ) -> profile ( ) ) ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }