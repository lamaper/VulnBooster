IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , UseCounterCSSPropertiesInIframe ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/use_counter_features_in_iframe.html" ) ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kCssPropertiesHistogramName , 6 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kCssPropertiesHistogramName , 7 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kCssPropertiesHistogramName , blink : : mojom : : kTotalPagesMeasuredCSSSampleId , 1 ) ;
 }