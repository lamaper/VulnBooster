IN_PROC_BROWSER_TEST_F ( HttpsEngagementPageLoadMetricsBrowserTest , Navigate_Both_NonHtmlMainResource ) {
 StartHttpServer ( ) ;
 StartHttpsServer ( false ) ;
 NavigateTwiceInTabAndClose ( http_test_server_ -> GetURL ( "/circle.svg" ) , https_test_server_ -> GetURL ( "/circle.svg" ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpEngagementHistogram , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHttpsEngagementHistogram , 1 ) ;
 }