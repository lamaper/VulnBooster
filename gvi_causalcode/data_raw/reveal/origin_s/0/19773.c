IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , LoadingMetrics ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_TIMING_INFO ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/title1.html" ) ) ;
 waiter -> Wait ( ) ;
 }