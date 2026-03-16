IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , InitialVisibilityOfSingleRestoredTab ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , GetTestURL ( ) ) ;
 histogram_tester_ . ExpectTotalCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , true , 1 ) ;
 Browser * new_browser = QuitBrowserAndRestore ( browser ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( WaitForTabsToLoad ( new_browser ) ) ;
 histogram_tester_ . ExpectTotalCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , 2 ) ;
 histogram_tester_ . ExpectBucketCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , true , 2 ) ;
 }