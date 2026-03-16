IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NoPaintForEmptyDocument ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_LAYOUT ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/empty.html" ) ) ;
 waiter -> Wait ( ) ;
 EXPECT_FALSE ( waiter -> DidObserveInPage ( TimingField : : FIRST_PAINT ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstLayout , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramLoad , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstPaint , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstContentfulPaint , 0 ) ;
 }