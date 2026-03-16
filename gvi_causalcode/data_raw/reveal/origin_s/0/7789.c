IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , PRE_TestSessionRestore ) {
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) ) ) ;
 AddBlankTabAndShow ( browser ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( chrome : : kChromeUIAboutURL ) ) ) ;
 PrepareForDialog ( browser ( ) ) ;
 RepeatedNotificationObserver cancel_observer ( chrome : : NOTIFICATION_BROWSER_CLOSE_CANCELLED , 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 ASSERT_NO_FATAL_FAILURE ( CancelClose ( ) ) ;
 cancel_observer . Wait ( ) ;
 EXPECT_FALSE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 browser ( ) -> tab_strip_model ( ) -> CloseWebContentsAt ( 1 , TabStripModel : : CLOSE_USER_GESTURE ) ;
 content : : TestNavigationObserver navigation_observer ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , 1 ) ;
 ASSERT_NO_FATAL_FAILURE ( NavigateToURLWithDisposition ( browser ( ) , GURL ( chrome : : kChromeUIVersionURL ) , WindowOpenDisposition : : CURRENT_TAB , ui_test_utils : : BROWSER_TEST_NONE ) ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 navigation_observer . Wait ( ) ;
 RepeatedNotificationObserver close_observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , 1 ) ;
 chrome : : CloseAllBrowsersAndQuit ( ) ;
 close_observer . Wait ( ) ;
 EXPECT_TRUE ( browser_shutdown : : IsTryingToQuit ( ) ) ;
 EXPECT_TRUE ( BrowserList : : GetInstance ( ) -> empty ( ) ) ;
 }