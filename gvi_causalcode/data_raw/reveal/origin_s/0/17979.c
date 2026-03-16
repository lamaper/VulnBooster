IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , MAYBE_TestUnloadMultipleSlowTabs ) {
 const int kTabCount = 5 ;
 const int kResposiveTabIndex = 2 ;
 for ( int i = 0 ;
 i < kTabCount ;
 i ++ ) {
 if ( i ) AddBlankTabAndShow ( browsers_ [ 0 ] ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browsers_ [ 0 ] , embedded_test_server ( ) -> GetURL ( ( i == kResposiveTabIndex ) ? "/beforeunload.html" : "/beforeunload_slow.html" ) ) ) ;
 }
 PrepareForDialog ( browsers_ [ 0 ] -> tab_strip_model ( ) -> GetWebContentsAt ( kResposiveTabIndex ) ) ;
 RepeatedNotificationObserver cancel_observer ( chrome : : NOTIFICATION_BROWSER_CLOSE_CANCELLED , 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( CancelClose ( ) ) ;
 cancel_observer . Wait ( ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_EQ ( kTabCount , browsers_ [ 0 ] -> tab_strip_model ( ) -> count ( ) ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }