IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , LoadingAfterSessionRestore ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , GetTestURL ( ) ) ;
 Browser * new_browser = nullptr ;
 {
 SessionRestorePaintWaiter session_restore_paint_waiter ;
 new_browser = QuitBrowserAndRestore ( browser ( ) ) ;
 session_restore_paint_waiter . WaitForForegroundTabs ( 1 ) ;
 ExpectFirstPaintMetricsTotalCount ( 1 ) ;
 }
 auto waiter = std : : make_unique < PageLoadMetricsWaiter > ( new_browser -> tab_strip_model ( ) -> GetActiveWebContents ( ) ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_MEANINGFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( new_browser , GetTestURL ( ) ) ;
 waiter -> Wait ( ) ;
 ExpectFirstPaintMetricsTotalCount ( 1 ) ;
 }