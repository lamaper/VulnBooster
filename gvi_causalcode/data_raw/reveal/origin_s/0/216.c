IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , Navigate_Both ) {
 StartHttpServer ( ) ;
 StartHttpsServer ( false ) ;
 NavigateTwiceInTabAndClose ( http_test_server_ -> GetURL ( "/simple.html" ) , https_test_server_ -> GetURL ( "/simple.html" ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 1 ) ;
 }