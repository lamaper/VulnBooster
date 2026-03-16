IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , SameOrigin_Http ) {
 StartHttpServer ( ) ;
 NavigateTwiceInTabAndClose ( http_test_server_ -> GetURL ( "/simple.html" ) , http_test_server_ -> GetURL ( "/empty.html" ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 2 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 0 ) ;
 }