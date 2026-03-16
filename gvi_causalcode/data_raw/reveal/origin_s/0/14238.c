IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , Navigate_Https ) {
 StartHttpsServer ( false ) ;
 NavigateTwiceInTabAndClose ( https_test_server_ -> GetURL ( "/simple.html" ) , GURL ( chrome : : kChromeUIVersionURL ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 1 ) ;
 FakeUserMetricsUpload ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementSessionPercentage , 1 ) ;
 int32_t ratio_bucket = histogram_tester_ . GetAllSamples ( internal : : kHttpsEngagementSessionPercentage ) [ 0 ] . min ;
 EXPECT_EQ ( 100 , ratio_bucket ) ;
 }