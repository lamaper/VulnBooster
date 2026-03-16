IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , ClosedWhileHidden_Https ) {
 StartHttpsServer ( false ) ;
 base : : TimeDelta upper_bound = NavigateInForegroundAndCloseInBackgroundWithTiming ( https_test_server_ -> GetURL ( "/simple.html" ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 1 ) ;
 int32_t bucket_min = histogram_tester_ . GetAllSamples ( internal : : kHttpsEngagementHistogram ) [ 0 ] . min ;
 EXPECT_GE ( upper_bound . InMilliseconds ( ) , bucket_min ) ;
 EXPECT_LT ( 0 , bucket_min ) ;
 }