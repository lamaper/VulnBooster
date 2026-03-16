IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , NavigationDuringSessionRestore ) {
 NavigateToUntrackedUrl ( ) ;
 Browser * new_browser = QuitBrowserAndRestore ( browser ( ) ) ;
 auto waiter = std : : make_unique < PageLoadMetricsWaiter > ( new_browser -> tab_strip_model ( ) -> GetActiveWebContents ( ) ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_MEANINGFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( new_browser , GetTestURL ( ) ) ;
 waiter -> Wait ( ) ;
 ExpectFirstPaintMetricsTotalCount ( 0 ) ;
 }