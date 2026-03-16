IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , OtherScheme ) {
 NavigateInForegroundAndCloseWithTiming ( GURL ( chrome : : kChromeUIVersionURL ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 0 ) ;
 }