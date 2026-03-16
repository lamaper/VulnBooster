IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , UseCounterFeaturesMixedContent ) {
 net : : EmbeddedTestServer https_server ( net : : EmbeddedTestServer : : TYPE_HTTPS ) ;
 https_server . AddDefaultHandlers ( base : : FilePath ( FILE_PATH_LITERAL ( "chrome/test/data" ) ) ) ;
 ASSERT_TRUE ( https_server . Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , https_server . GetURL ( "/page_load_metrics/use_counter_features.html" ) ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kMixedContentAudio ) , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kMixedContentImage ) , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kMixedContentVideo ) , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kPageVisits ) , 1 ) ;
 }