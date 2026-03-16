IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , HttpErrorPage ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/404.html" ) ) ;
 NavigateToUntrackedUrl ( ) ;
 EXPECT_TRUE ( NoPageLoadMetricsRecorded ( ) ) << "Recorded metrics: " << GetRecordedPageLoadMetricNames ( ) ;
 }