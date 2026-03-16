IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , UseCounterFeaturesInNonSecureMainFrame ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "non-secure.test" , "/page_load_metrics/use_counter_features.html" ) ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kTextWholeText ) , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kV8Element_Animate_Method ) , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kNavigatorVibrate ) , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kDataUriHasOctothorpe ) , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kApplicationCacheManifestSelectInsecureOrigin ) , 1 ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kPageVisits ) , 1 ) ;
 }