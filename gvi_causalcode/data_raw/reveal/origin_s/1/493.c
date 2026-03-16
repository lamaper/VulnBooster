IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , Navigate_Http ) {
 StartHttpServer ( ) ;
 NavigateTwiceInTabAndClose ( http_test_server_ -> GetURL ( "/simple.html" ) , GURL ( chrome : : kChromeUIVersionURL ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 0 ) ;
 }