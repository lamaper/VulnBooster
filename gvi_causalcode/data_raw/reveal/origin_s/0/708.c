IN_PROC_BROWSER_TEST_F ( SessionRestorePageLoadMetricsBrowserTest , InitialVisibilityOfMultipleRestoredTabs ) {
 ui_test_utils : : NavigateToURL ( browser ( ) , GetTestURL ( ) ) ;
 ui_test_utils : : NavigateToURLWithDisposition ( browser ( ) , GetTestURL ( ) , WindowOpenDisposition : : NEW_BACKGROUND_TAB , ui_test_utils : : BROWSER_TEST_WAIT_FOR_NAVIGATION ) ;
 histogram_tester_ . ExpectTotalCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , 2 ) ;
 histogram_tester_ . ExpectBucketCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , false , 1 ) ;
 Browser * new_browser = QuitBrowserAndRestore ( browser ( ) ) ;
 ASSERT_NO_FATAL_FAILURE ( WaitForTabsToLoad ( new_browser ) ) ;
 TabStripModel * tab_strip = new_browser -> tab_strip_model ( ) ;
 ASSERT_TRUE ( tab_strip ) ;
 ASSERT_EQ ( 2 , tab_strip -> count ( ) ) ;
 histogram_tester_ . ExpectTotalCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , 4 ) ;
 histogram_tester_ . ExpectBucketCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , true , 2 ) ;
 histogram_tester_ . ExpectBucketCount ( page_load_metrics : : internal : : kPageLoadStartedInForeground , false , 2 ) ;
 }