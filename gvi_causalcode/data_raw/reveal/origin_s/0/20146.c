IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , PaintInChildFrame ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 GURL a_url ( embedded_test_server ( ) -> GetURL ( "/page_load_metrics/iframe.html" ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_LAYOUT ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 waiter -> AddSubFrameExpectation ( TimingField : : FIRST_PAINT ) ;
 waiter -> AddSubFrameExpectation ( TimingField : : FIRST_CONTENTFUL_PAINT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , a_url ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstLayout , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramLoad , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstPaint , 1 ) ;
 }