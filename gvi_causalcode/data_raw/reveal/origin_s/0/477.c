IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , NoPaintForEmptyDocumentInChildFrame ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL a_url ( embedded_test_server ( ) -> GetURL ( "/page_load_metrics/empty_iframe.html" ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_LAYOUT ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 waiter -> AddSubFrameExpectation ( TimingField : : FIRST_LAYOUT ) ;
 waiter -> AddSubFrameExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , a_url ) ;
 waiter -> Wait ( ) ;
 EXPECT_FALSE ( waiter -> DidObserveInPage ( TimingField : : FIRST_PAINT ) ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstLayout , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramLoad , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstPaint , 0 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstContentfulPaint , 0 ) ;
 }