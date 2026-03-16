IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NonHttpOrHttpsUrl ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , GURL ( chrome : : kChromeUIVersionURL ) ) ;
 NavigateToUntrackedUrl ( ) ;
 EXPECT_TRUE ( NoPageLoadMetricsRecorded ( ) ) << "Recorded metrics: " << GetRecordedPageLoadMetricNames ( ) ;
 }