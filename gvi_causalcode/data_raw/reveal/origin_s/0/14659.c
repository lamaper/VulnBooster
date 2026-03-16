IN_PROC_BROWSER_TEST_P ( BrowserCloseManagerBrowserTest , MAYBE_AddBeforeUnloadDuringClosing ) {
 if ( GetParam ( ) ) return ;
 ASSERT_NO_FATAL_FAILURE ( ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) , WindowOpenDisposition : : NEW_WINDOW , ui_test_utils : : BROWSER_TEST_WAIT_FOR_BROWSER ) ;
 EXPECT_EQ ( 2u , BrowserList : : GetInstance ( ) -> size ( ) ) ;
 auto * browser2 = BrowserList : : GetInstance ( ) -> get ( 0 ) != browser ( ) ? BrowserList : : GetInstance ( ) -> get ( 0 ) : BrowserList : : GetInstance ( ) -> get ( 1 ) ;
 content : : WaitForLoadStop ( browser2 -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) ) ;
 EXPECT_TRUE ( browser2 -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) -> NeedToFireBeforeUnload ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser2 , embedded_test_server ( ) -> GetURL ( "/title2.html" ) , WindowOpenDisposition : : NEW_FOREGROUND_TAB , ui_test_utils : : BROWSER_TEST_WAIT_FOR_NAVIGATION ) ;
 content : : WaitForLoadStop ( browser2 -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) ) ;
 EXPECT_FALSE ( browser2 -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) -> NeedToFireBeforeUnload ( ) ) ;
 EXPECT_EQ ( 2 , browser2 -> tab_strip_model ( ) -> count ( ) ) ;
 PrepareForDialog ( browser2 ) ;
 TabRestoreServiceChangesObserver restore_observer ( browser2 -> profile ( ) ) ;
 content : : WindowedNotificationObserver observer ( chrome : : NOTIFICATION_BROWSER_CLOSED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : CloseWindow ( browser2 ) ;
 content : : RunAllPendingInMessageLoop ( ) ;
 EXPECT_EQ ( 2u , BrowserList : : GetInstance ( ) -> size ( ) ) ;
 ASSERT_TRUE ( content : : ExecuteScript ( browser2 -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) -> GetRenderViewHost ( ) , "window.addEventListener('beforeunload', " "function(event) {
 event.returnValue = 'Foo';
 }
);
" ) ) ;
 EXPECT_TRUE ( browser2 -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) -> NeedToFireBeforeUnload ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 content : : RunAllPendingInMessageLoop ( ) ;
 EXPECT_EQ ( 2u , BrowserList : : GetInstance ( ) -> size ( ) ) ;
 EXPECT_EQ ( 2 , browser2 -> tab_strip_model ( ) -> count ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( AcceptClose ( ) ) ;
 observer . Wait ( ) ;
 EXPECT_EQ ( 1u , BrowserList : : GetInstance ( ) -> size ( ) ) ;
 EXPECT_EQ ( browser ( ) , BrowserList : : GetInstance ( ) -> get ( 0 ) ) ;
 EXPECT_EQ ( 1u , restore_observer . changes_count ( ) ) ;
 content : : WindowedNotificationObserver open_window_observer ( chrome : : NOTIFICATION_BROWSER_OPENED , content : : NotificationService : : AllSources ( ) ) ;
 chrome : : OpenWindowWithRestoredTabs ( browser ( ) -> profile ( ) ) ;
 open_window_observer . Wait ( ) ;
 EXPECT_EQ ( 2u , BrowserList : : GetInstance ( ) -> size ( ) ) ;
 browser2 = BrowserList : : GetInstance ( ) -> get ( 0 ) != browser ( ) ? BrowserList : : GetInstance ( ) -> get ( 0 ) : BrowserList : : GetInstance ( ) -> get ( 1 ) ;
 EXPECT_EQ ( 2 , browser2 -> tab_strip_model ( ) -> count ( ) ) ;
 EXPECT_EQ ( embedded_test_server ( ) -> GetURL ( "/beforeunload.html" ) , browser2 -> tab_strip_model ( ) -> GetWebContentsAt ( 0 ) -> GetURL ( ) ) ;
 EXPECT_EQ ( embedded_test_server ( ) -> GetURL ( "/title2.html" ) , browser2 -> tab_strip_model ( ) -> GetWebContentsAt ( 1 ) -> GetURL ( ) ) ;
 }