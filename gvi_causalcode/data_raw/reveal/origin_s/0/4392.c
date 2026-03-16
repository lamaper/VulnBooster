IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , SingleTabSessionRestore ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , GetTestURL ( ) ) ;
 SessionRestorePaintWaiter session_restore_paint_waiter ;
 QuitBrowserAndRestore ( browser ( ) ) ;
 session_restore_paint_waiter . WaitForForegroundTabs ( 1 ) ;
 ExpectFirstPaintMetricsTotalCount ( 1 ) ;
 }