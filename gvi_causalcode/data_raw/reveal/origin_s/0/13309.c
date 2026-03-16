IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , PayloadSizeChildFrame ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/large_iframe.html" ) ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramPageLoadTotalBytes , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kHistogramPageLoadTotalBytes , 10 , 1 ) ;
 }