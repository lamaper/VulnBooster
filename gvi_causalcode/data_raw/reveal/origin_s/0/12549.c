IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , Navigate_Both_NonHtmlMainResource ) {
 StartHttpServer ( ) ;
 StartHttpsServer ( false ) ;
 NavigateTwiceInTabAndClose ( http_test_server_ -> GetURL ( "/circle.svg" ) , https_test_server_ -> GetURL ( "/circle.svg" ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 1 ) ;
 FakeUserMetricsUpload ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementSessionPercentage , 1 ) ;
 int32_t ratio_bucket = histogram_tester_ . GetAllSamples ( internal : : kHttpsEngagementSessionPercentage ) [ 0 ] . min ;
 EXPECT_GT ( 100 , ratio_bucket ) ;
 EXPECT_LT ( 0 , ratio_bucket ) ;
 }