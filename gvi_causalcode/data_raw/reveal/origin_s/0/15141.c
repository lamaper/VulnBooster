IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , MultipleUploads ) {
 StartHttpsServer ( false ) ;
 NavigateInForegroundAndCloseWithTiming ( https_test_server_ -> GetURL ( "/" ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementSessionPercentage , 0 ) ;
 FakeUserMetricsUpload ( ) ;
 FakeUserMetricsUpload ( ) ;
 FakeUserMetricsUpload ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementSessionPercentage , 1 ) ;
 }