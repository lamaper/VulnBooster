IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , FirstMeaningfulPaintNotRecorded ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_CONTENTFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/page_with_active_connections.html" ) ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstContentfulPaint , 1 ) ;
 histogram_tester_ . ExpectUniqueSample ( internal : : kHistogramFirstMeaningfulPaintStatus , internal : : FIRST_MEANINGFUL_PAINT_DID_NOT_REACH_NETWORK_STABLE , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstMeaningfulPaint , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramParseStartToFirstMeaningfulPaint , 0 ) ;
 }