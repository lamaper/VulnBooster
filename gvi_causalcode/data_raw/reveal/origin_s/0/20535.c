IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , ChromeErrorPage ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/title1.html" ) ;
 ASSERT_TRUE ( embedded_test_server ( ) -> ShutdownAndWaitUntilComplete ( ) ) ;
 content : : NavigationHandleObserver observer ( browser ( ) -> tab_strip_model ( ) -> GetActiveWebContents ( ) , url ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 ASSERT_TRUE ( observer . is_error ( ) ) ;
 NavigateToUntrackedUrl ( ) ;
 EXPECT_TRUE ( NoPageLoadMetricsRecorded ( ) ) << "Recorded metrics: " << GetRecordedPageLoadMetricNames ( ) ;
 }