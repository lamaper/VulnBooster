IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , MultipleSessionRestores ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , GetTestURL ( ) ) ;
 Browser * current_browser = browser ( ) ;
 const int num_session_restores = 3 ;
 for ( int i = 1 ;
 i <= num_session_restores ;
 ++ i ) {
 SessionRestorePaintWaiter session_restore_paint_waiter ;
 current_browser = QuitBrowserAndRestore ( current_browser ) ;
 session_restore_paint_waiter . WaitForForegroundTabs ( 1 ) ;
 ExpectFirstPaintMetricsTotalCount ( i ) ;
 }
 }