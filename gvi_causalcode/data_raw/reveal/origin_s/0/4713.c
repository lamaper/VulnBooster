IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , TestAddTabDuringShutdown ) {
 browsers_ . push_back ( CreateBrowser ( browser ( ) -> profile ( ) ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 0 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 1 ] , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) ) ) ;
 PrepareForDialog ( browsers_ [ 0 ] ) ;
 PrepareForDialog ( browsers_ [ 1 ] ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 2 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 AddBlankTabAndShow ( browsers_ [ 0 ] ) ;
 AddBlankTabAndShow ( browsers_ [ 1 ] ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }