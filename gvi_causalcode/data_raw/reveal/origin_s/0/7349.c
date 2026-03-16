IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , Navigate_Http ) {
 StartHttpServer ( ) ;
 NavigateTwiceInTabAndClose ( http_test_server_ -> GetURL ( "/simple.html" ) , GURL ( chrome : : kChromeUIVersionURL ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 0 ) ;
 FakeUserMetricsUpload ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementSessionPercentage , 1 ) ;
 int32_t ratio_bucket = histogram_tester_ . GetAllSamples ( internal : : kHttpsEngagementSessionPercentage ) [ 0 ] . min ;
 EXPECT_EQ ( 0 , ratio_bucket ) ;
 }