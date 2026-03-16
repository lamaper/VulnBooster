IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NoNavigation ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 EXPECT_TRUE ( NoPageLoadMetricsRecorded ( ) ) << "Recorded metrics: " << GetRecordedPageLoadMetricNames ( ) ;
 }