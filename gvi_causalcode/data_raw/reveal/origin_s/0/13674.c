IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , SameDocumentNavigation ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : FIRST_LAYOUT ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 waiter -> Wait ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDomContentLoaded , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramLoad , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstLayout , 1 ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/title1.html#hash" ) ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramDomContentLoaded , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramLoad , 1 ) ;
 histogram_tester_ . ExpectTotalCount ( internal : : kHistogramFirstLayout , 1 ) ;
 }