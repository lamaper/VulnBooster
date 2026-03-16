IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , AlwaysInBackground ) {
 StartHttpsServer ( false ) ;
 StartHttpServer ( ) ;
 NavigateInBackgroundAndClose ( https_test_server_ -> GetURL ( "/simple.html" ) ) ;
 NavigateInBackgroundAndClose ( http_test_server_ -> GetURL ( "/simple.html" ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 0 ) ;
 FakeUserMetricsUpload ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementSessionPercentage , 0 ) ;
 }