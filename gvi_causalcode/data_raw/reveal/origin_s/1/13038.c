IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , UncommittedLoadWithError ) {
 StartHttpsServer ( true ) ;
 TabStripModel * tab_strip_model = browser ( ) -> tab_strip_model ( ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , https_test_server_ -> GetURL ( "/simple.html" ) ) ;
 content : : WebContentsDestroyedWatcher destroyed_watcher ( tab_strip_model -> GetActiveWebContents ( ) ) ;
 EXPECT_TRUE ( tab_strip_model -> CloseWebContentsAt ( tab_strip_model -> active_index ( ) , 0 ) ) ;
 destroyed_watcher . Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 0 ) ;
 }