IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , MultipleTabsSessionRestore ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , GetTestURL ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , GetTestURL ( ) , WindowOpenDisposition : : NEW_BACKGROUND_TAB , ui_test_utils : : BROWSER_TEST_WAIT_FOR_NAVIGATION ) ;
 SessionRestorePaintWaiter session_restore_paint_waiter ;
 Browser * new_browser = QuitBrowserAndRestore ( browser ( ) ) ;
 TabStripModel * tab_strip = new_browser -> tab_strip_model ( ) ;
 ASSERT_TRUE ( tab_strip ) ;
 ASSERT_EQ ( 2 , tab_strip -> count ( ) ) ;
 session_restore_paint_waiter . WaitForForegroundTabs ( 1 ) ;
 ASSERT_NO_FATAL_FAILURE ( WaitForTabsToLoad ( new_browser ) ) ;
 ExpectFirstPaintMetricsTotalCount ( 1 ) ;
 }