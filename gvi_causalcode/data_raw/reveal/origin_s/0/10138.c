IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NonHtmlMainResource ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/circle.svg" ) ) ;
 NavigateToUntrackedUrl ( ) ;
 EXPECT_TRUE ( NoPageLoadMetricsRecorded ( ) ) << "Recorded metrics: " << GetRecordedPageLoadMetricNames ( ) ;
 }