IN_PROC_BROWSER_TEST_F ( PageLoadMetricsBrowserTest , UseCounterUkmFeaturesLogged ) {
 ASSERT_TRUE ( embedded_test_server ( ) -> Start ( ) ) ;
 auto waiter = CreatePageLoadMetricsWaiter ( ) ;
 waiter -> AddPageExpectation ( TimingField : : LOAD_EVENT ) ;
 GURL url = embedded_test_server ( ) -> GetURL ( "/page_load_metrics/use_counter_features.html" ) ;
 ui_test_utils : : NavigateToURL ( browser ( ) , url ) ;
 waiter -> Wait ( ) ;
 NavigateToUntrackedUrl ( ) ;
 const auto & entries = test_ukm_recorder_ -> GetEntriesByName ( internal : : kUkmUseCounterEventName ) ;
 EXPECT_EQ ( 3u , entries . size ( ) ) ;
 std : : vector < int64_t > ukm_features ;
 for ( const auto * entry : entries ) {
 test_ukm_recorder_ -> ExpectEntrySourceHasUrl ( entry , url ) ;
 const auto * metric = test_ukm_recorder_ -> GetEntryMetric ( entry , internal : : kUkmUseCounterFeature ) ;
 EXPECT_TRUE ( metric ) ;
 ukm_features . push_back ( * metric ) ;
 }
 EXPECT_THAT ( ukm_features , UnorderedElementsAre ( static_cast < int64_t > ( WebFeature : : kNavigatorVibrate ) , static_cast < int64_t > ( WebFeature : : kDataUriHasOctothorpe ) , static_cast < int64_t > ( WebFeature : : kApplicationCacheManifestSelectSecureOrigin ) ) ) ;
 }