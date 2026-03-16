IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , UseCounterAnimatedCSSPropertiesMixedContent ) {
 net : : EmbeddedTestServer https_server ( net : : EmbeddedTestServer : : TYPE_HTTPS ) ;
 https_server . AddDefaultHandlers ( base : : FilePath ( FILE_PATH_LITERAL ( "chrome/test/data" ) ) ) ;
 ASSERT_TRUE ( https_server . Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , https_server . GetURL ( "/page_load_metrics/use_counter_features.html" ) ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kAnimatedCssPropertiesHistogramName , 161 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kAnimatedCssPropertiesHistogramName , 91 , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kAnimatedCssPropertiesHistogramName , blink : : mojom : : kTotalPagesMeasuredCSSSampleId , 1 ) ;
 }