IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , NoSessionRestore ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , GetTestURL ( ) ) ;
 ExpectFirstPaintMetricsTotalCount ( 0 ) ;
 }