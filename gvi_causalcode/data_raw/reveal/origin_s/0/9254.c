IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , BackgroundThenForeground_Https ) {
 StartHttpsServer ( false ) ;
 base : : TimeDelta upper_bound = NavigateInBackgroundAndCloseInForegroundWithTiming ( https_test_server_ -> GetURL ( "/simple.html" ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 1 ) ;
 int32_t bucket_min = histogram_tester_ . GetAllSamples ( internal : : kHttpsEngagementHistogram ) [ 0 ] . min ;
 EXPECT_GE ( upper_bound . InMilliseconds ( ) , bucket_min ) ;
 EXPECT_LT ( 0 , bucket_min ) ;
 FakeUserMetricsUpload ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementSessionPercentage , 1 ) ;
 int32_t ratio_bucket = histogram_tester_ . GetAllSamples ( internal : : kHttpsEngagementSessionPercentage ) [ 0 ] . min ;
 EXPECT_EQ ( 100 , ratio_bucket ) ;
 }