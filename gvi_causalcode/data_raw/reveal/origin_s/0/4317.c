IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , UseCounterObserveSVGImagePage ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , embedded_test_server ( ) -> GetURL ( "/page_load_metrics/circle.svg" ) ) ;
 NavigateToUntrackedUrl ( ) ;
 histogram_tester_ . ExpectBucketCount ( internal : : kFeaturesHistogramName , static_cast < int32_t > ( WebFeature : : kPageVisits ) , 1 ) ;
 }