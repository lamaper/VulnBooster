IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , UseCounterAnimatedCSSPropertiesInMainFrame ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/use_counter_features.html" ) ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kAnimatedCssPropertiesHistogramName , 161 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kAnimatedCssPropertiesHistogramName , 91 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kAnimatedCssPropertiesHistogramName , blink : : mojom : : kTotalPagesMeasuredCSSSampleId , 1 ) ;
 }