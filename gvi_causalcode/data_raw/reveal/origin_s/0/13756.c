IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , LoadingMetricsFailed ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_TIMING_INFO ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/404.html" ) ) ;
 waiter -> Wait ( ) ;
 }