IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , MAYBE_TestBeforeUnloadMultipleSlowWindows ) {
 const int kBrowserCount = 5 ;
 const int kResposiveBrowserIndex = 2 ;
 for ( int i = 0 ;
 i < kBrowserCount ;
 i ++ ) {
 if ( i ) browsers_ . push_back ( CreateBrowser ( browser ( ) -> profile ( ) ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ i ] , embedded_test_server ( ) -> GetURL ( ( i == kResposiveBrowserIndex ) ? "/beforeunload.html" : "/beforeunload_slow.html" ) ) ) ;
 }
 PrepareForDialog ( browsers_ [ kResposiveBrowserIndex ] ) ;
 RepeatedNotificationObserver cancel_observer ( chrome : : NOTIFICATION_BROWSER_CLOSE_CANCELLED , kResposiveBrowserIndex + 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( CancelClose ( ) ) ;
 cancel_observer . Wait ( ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 for ( int i = 0 ;
 i < kBrowserCount ;
 i ++ ) EXPECT_EQ ( 1 , browsers_ [ i ] -> tab_strip_model ( ) -> count ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , kBrowserCount ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }